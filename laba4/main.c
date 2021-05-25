#include <windows.h>
#include <math.h>
#include <stdio.h>
double** arr(int n) {
    double** matrix = (double**)malloc(sizeof(double) * n);
    for(int i = 0; i < n; i++) matrix[i] = (double*)malloc(sizeof(double) * n);
    return matrix;
}
double** randm(int n) {
    double** matrix = arr(n);
    srand(0405);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            double a = rand() % 10;
            matrix[i][j] = 2 * (a / 10);
        }
    }
    return matrix;
}
double** mulmr(double coef, double **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = matrix[i][j] * coef;
            if (matrix[i][j] > 1) matrix[i][j] = 1;
            else matrix[i][j] = 0;
        }
    }
    return matrix;
}
void print_matrix(double ** A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
                printf("%.0f ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char prog_name[] = "Laba 4";
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpszCmdLine, int nCmdShow) {
    WNDCLASS w;
    w.lpszClassName = prog_name;
    w.hInstance = hInstance;
    w.lpfnWndProc = WndProc;
    w.hCursor = LoadCursor(NULL, IDC_ARROW);
    w.hIcon = 0;
    w.lpszMenuName = 0;
    w.hbrBackground = WHITE_BRUSH;
    w.style = CS_HREDRAW|CS_VREDRAW;
    w.cbClsExtra = 0;
    w.cbWndExtra = 0;
    if (!RegisterClass(&w)) return 0;
    HWND hWnd;
    MSG lpMsg;
    hWnd=CreateWindow(prog_name, "Laba 4. Nikita Gryshchak",
        WS_OVERLAPPEDWINDOW,
        100, //положення верхнього кута вікна на екрані по х
        100, // положення верхнього кута вікна на екрані по y
        800, //ширина
        800, //висота
        (HWND)NULL,
        (HMENU)NULL,
        (HINSTANCE)hInstance,
        (HINSTANCE)NULL
    );
    ShowWindow(hWnd, nCmdShow);
    while (GetMessage(&lpMsg, hWnd, 0, 0)) {
        TranslateMessage(&lpMsg);
        DispatchMessage(&lpMsg);
    }
    return(lpMsg.wParam);
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam) {
    HDC hdc;
    PAINTSTRUCT ps;
    void arrow(float fi, int px,int py) {
        fi = M_PI * (180.0 - fi) / 180.0;
        int lx, ly, rx, ry;
        lx = px + 15 * cos(fi + 0.3);
        rx = px + 15 * cos(fi - 0.3);
        ly = py + 15 * sin(fi + 0.3);
        ry = py + 15 * sin(fi - 0.3);
        MoveToEx(hdc, lx, ly, NULL);
        LineTo(hdc, px, py);
        LineTo(hdc, rx, ry);
    }
    void larrow_to(double fromX, double fromY, double toX, double toY) {
        double difX = toX - fromX;
        double difY = toY - fromY;
        double arctg = atan(fabs(difY) / fabs(difX)) * 180 / M_PI;
        double angl, opposit_angl;
        if (difX >= 0 && difY < 0) angl = arctg, opposit_angl = M_PI / 180 * (angl + 180);
        else if (difX < 0 && difY < 0) angl = 180 - arctg, opposit_angl = M_PI / 180 * (angl + 180);
        else if (difX < 0 && difY >= 0) angl = 180 + arctg, opposit_angl = M_PI / 180 * (angl - 180);
        else angl = 360 - arctg, opposit_angl = M_PI / 180 * (angl - 180);
        MoveToEx(hdc, fromX, fromY, NULL);
        LineTo(hdc, toX, toY);
        arrow(angl, toX + 16 * cos(opposit_angl), toY - 16 * sin(opposit_angl));
    }
    void broken_larrow(double x1, double y1, double x2, double y2, int div, int t, double** A, int i, int j) {
        double s = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2)) / div + t;
        double xO = (x1 + x2) / 2, yO = (y1 + y2) / 2;
        double xAO = xO - x1, yAO = y1 - yO;
        double xOM, yOM;
        if ((x2 - x1) < 0 && (y2 - y1) != 0 && A[j][i] != 1) {
            yOM = -1 * xAO * s / sqrt(xAO * xAO + yAO * yAO);
            xOM = -1 * yAO * yOM / xAO;
        }
        else {
            yOM = xAO * s / sqrt(xAO * xAO + yAO * yAO);
            xOM = -1 * yAO * yOM / xAO;
        }
        double xAM = xAO + xOM, yAM = yAO + yOM;
        double xM = x1 + xAM, yM = y1 - yAM;
        MoveToEx(hdc, x1, y1, NULL);
        LineTo(hdc, xM, yM);
        larrow_to(xM, yM, x2, y2);
    }
    switch (messg) {
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            char* nn[10] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
            int nx[10] = {169};
            int ny[10] = {600};
            int dx = 16, dy = 16, dtx = 5;
            for (int i = 1; i < 4; i++) {
                nx[i] = nx[i - 1] + 77;
                ny[i] = ny[i - 1] - 154;
            }
            for (int i = 4; i < 7; i++) {
                nx[i] = nx[i - 1] + 77;
                ny[i] = ny[i - 1] + 154;
            }
            for (int i = 7; i < 10; i++) {
                nx[i] = nx[i - 1] - 115.5;
                ny[i] = ny[i - 1];
            }
            int bad_targets[10][10] = {
                {0, 0, 1, 1, 0, 0, 1, 1, 1, 0},
                {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {1, 1, 0, 0, 0, 1, 1, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
                {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
                {1, 0, 0, 1, 1, 0, 0, 0, 1, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 1, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 1, 1, 0, 0}
            };
            HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
            HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
            double** T = randm(10);
            double** A = mulmr(0.7 - 5 * 0.01, T, 10);
            printf("Matriza sumiznosti: \n");
            print_matrix(A, 10);
            int degOut[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            int degIn[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    degOut[i] += A[i][j];
                    degIn[i] += A[j][i];
                }
                printf("%d: Napivstepin vihody = %d; Napivstepin vhody = %d\n", i + 1, degOut[i], degIn[i]);
            }
            printf("\n");
            int t = 0;
            printf("Visachi vershini: ");
            for (int i = 0; i < 10; i++) {
                if (degOut[i] + degIn[i] == 1) {
                    t = 1;
                    printf("%d ", i + 1);
                }
                if (i == 9 && t == 0) printf("nemae"); 
            }
            t = 0;
            printf("\nIzolovani vershini: ");
            for (int i = 0; i < 10; i++) {
                if (degOut[i] + degIn[i] == 0) {
                    t = 1;
                    printf("%d ", i + 1);
                }
                if (i == 9 && t == 0) printf("nemae");
            }
            printf("\n\n");
            SelectObject(hdc, KPen);
            for (int i = 0; i < 10; i++) {                              //drawing
                for (int j = 0; j < 10; j++) {
                    if (A[i][j] == 1) {
                        if (i == j) {                                   //if pointing on itself
                            if (i >= 0 && i < 4) {
                                Arc(hdc, nx[j], ny[j], nx[j]-40, ny[j]-40, nx[j], ny[j], nx[j], ny[j]);
                                arrow(0, nx[j]-16,ny[j]-2);
                            }
                            else if (i >= 4 && i < 7) {
                                Arc(hdc, nx[j], ny[j], nx[j]+40, ny[j]-40, nx[j], ny[j], nx[j], ny[j]);
                                arrow(180, nx[j]+16,ny[j]-2);
                            }
                            else {
                                Arc(hdc, nx[j], ny[j], nx[j]-40, ny[j]+40, nx[j], ny[j], nx[j], ny[j]);
                                arrow(90, nx[j]-2,ny[j]+16);
                            }
                        }
                        else if (A[j][i] == 1) broken_larrow(nx[i], ny[i], nx[j], ny[j], 20, 32, A, i, j);
                        else if (bad_targets[i][j] == 1) {
                            broken_larrow(nx[i], ny[i], nx[j], ny[j], 8, 40, A, i, j);    //if bad target
                        }
                        else larrow_to(nx[i], ny[i], nx[j], ny[j]);
                    }
                }
            }
            SelectObject(hdc, BPen);
            for (int i = 0; i < 10; i++) {                                  //вершини
                Ellipse(hdc, nx[i] - dx, ny[i] - dy, nx[i] + dx, ny[i] + dy);
                TextOut(hdc, nx[i] - dtx, ny[i] - dy / 2, nn[i], 2);
            }
            EndPaint(hWnd, &ps);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default: return(DefWindowProc(hWnd, messg, wParam, lParam));
    }
}