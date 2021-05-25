#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
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
            double a = rand();
            double res = 2 * a / RAND_MAX;
            matrix[i][j] = res;
        }
    }
    return matrix;
}
double** mulmr(double coef, double** matrix, int n) {
    double** res = arr(10);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i][j] = matrix[i][j] * coef;
            if (res[i][j] > 1) res[i][j] = 1;
            else res[i][j] = 0;
        }
    }
    return res;
}
double** roundm(double** matrix, int n) {
    double** res = arr(10);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i][j] = round(matrix[i][j]);
        }
    }
    return res;
}
double** matrixB(double** matrix, int n) {
    double** res = arr(10);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] > 0) res[i][j] = 1;
            else if (matrix[i][j] == 0) res[i][j] = 0;
        }
    }
    return res;
}
double** matrixC(double** matrix, int n) {
    double** res = arr(10);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] != matrix[j][i]) res[i][j] = 1;
            else res[i][j] = 0;
        }
    }
    return res;
}
double** matrixD(double** matrix, int n) {
    double** res = arr(10);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 1 && matrix[j][i] == 1) res[i][j] = 1;
            else res[i][j] = 0;
        }
    }
    return res;
}
double** matrixTr(int n) {
    double** res = arr(10);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j > i) res[i][j] = 1;
            else res[i][j] = 0;
        }
    }
    return res;
}
double** multiply(double** a, double** b, int n) {
    double** res = arr(10);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i][j] = a[i][j] * b[i][j];
        }
    }
    return res;
}
void print_matrix(double ** A) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
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
    hWnd=CreateWindow(prog_name, "Laba 5. Nikita Gryshchak",
        WS_OVERLAPPEDWINDOW,
        -10, //положення верхнього кута вікна на екрані по х
        0, // положення верхнього кута вікна на екрані по y
        1550, //ширина
        850, //висота
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
    HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
    HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
    HPEN TreePen = CreatePen(PS_SOLID, 5, RGB(100, 10, 10));
    int dx = 16, dy = 16, dtx = 5, veight = 0;
    void broken_line(double x1, double y1, double x2, double y2, int div, int t, double** W, int i, int j) {
        double s = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2)) / div + t;
        double xO = (x1 + x2) / 2, yO = (y1 + y2) / 2;
        double xAO = xO - x1, yAO = y1 - yO;
        double xOM, yOM;
        if ((x2 - x1) < 0 && (y2 - y1) != 0 && W[j][i] == 0) {
            yOM = -1 * xAO * s / sqrt(xAO * xAO + yAO * yAO);
            xOM = -1 * yAO * yOM / xAO;
        }
        else {
            yOM = xAO * s / sqrt(xAO * xAO + yAO * yAO);
            xOM = -1 * yAO * yOM / xAO;
        }
        double xAM = xAO + xOM, yAM = yAO + yOM;
        double xM = x1 + xAM, yM = y1 - yAM;
        double difX = xM - x1;
        double difY = yM - y1;
        double arctg = atan(fabs(difY) / fabs(difX));
        double angl, angl2;
        if (difX >= 0 && difY < 0) angl = arctg;
        else if (difX < 0 && difY < 0) angl = M_PI - arctg;
        else if (difX < 0 && difY >= 0) angl = M_PI + arctg;
        else angl = 2 * M_PI - arctg;
        MoveToEx(hdc, x1 + 16 * cos(angl), y1 - 16 * sin(angl), NULL);
        LineTo(hdc, xM, yM);
        difX = x2 - xM;
        difY = y2 - yM;
        arctg = atan(fabs(difY) / fabs(difX));
        if (difX >= 0 && difY < 0) angl2 = arctg + M_PI;
        else if (difX < 0 && difY < 0) angl2 = 2 * M_PI - arctg;
        else if (difX < 0 && difY >= 0) angl2 = arctg;
        else angl2 = M_PI - arctg;
        LineTo(hdc, x2 + 16 * cos(angl2), y2 - 16 * sin(angl2));
        char str[3];
        sprintf(str, "%.0f", W[i][j]);
        TextOut(hdc, xM - dtx, yM - dy / 2, str, 3);
    }
    void line_to(double x1, double y1, double x2, double y2, double** W, int i, int j) {
        double difX = x2 - x1;
        double difY = y2 - y1;
        double arctg = atan(fabs(difY) / fabs(difX));
        double angl, opposit_angl;
        if (difX >= 0 && difY < 0) angl = arctg, opposit_angl = angl + M_PI;
        else if (difX < 0 && difY < 0) angl = M_PI - arctg, opposit_angl = angl + M_PI;
        else if (difX < 0 && difY >= 0) angl = M_PI + arctg, opposit_angl = angl - M_PI;
        else angl = 2 * M_PI - arctg, opposit_angl = angl - M_PI;
        MoveToEx(hdc, x1 + 16 * cos(angl), y1 - 16 * sin(angl), NULL);
        LineTo(hdc, x2 + 16 * cos(opposit_angl), y2 - 16 * sin(opposit_angl));
        char str[3];
        sprintf(str, "%.0f", W[i][j]);
        TextOut(hdc, x1 + difX / 2 - 20 * cos(angl) - dtx, y1 + difY / 2 + 20 * sin(angl) - dy / 2, str, 3);
    }
    double** primAlgo(double** matrix, double** resTree, int start, int bad_targets[10][10], double nx[10], double ny[10], int visited[10]) {
        visited[start] = 1;
        int active = start, minimal = 100000000, minIndex = -1, flag = 0;
        flag = 0;
        for (int i = 0; i < 10; i++) {
            if (visited[i] == 0) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) return resTree;
        for (int i = 0; i < 10; i++) {
            if (matrix[active][i] > 0 && matrix[active][i] < minimal && visited[i] == 0) {
                minimal = matrix[active][i];
                minIndex = i;
            }
        }
        if (minIndex >= 0) {
            resTree[active][minIndex] = 1;
            visited[minIndex] = 1;
            veight += matrix[active][minIndex];
            sleep(1);
            if (bad_targets[active][minIndex] == 1) {
                broken_line(nx[active], ny[active], nx[minIndex], ny[minIndex], 18, 65, matrix, active, minIndex);    //if bad target
            }
            else line_to(nx[active], ny[active], nx[minIndex], ny[minIndex], matrix, active, minIndex);
            resTree = primAlgo(matrix, resTree, minIndex, bad_targets, nx, ny, visited);
        }
        else {
            return resTree;
        }
        resTree = primAlgo(matrix, resTree, active, bad_targets, nx, ny, visited);
        return resTree;
    }
    switch (messg) {
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            char* nn[10] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
            double nx[10] = {40}, nx2[10] = {830};
            double ny[10] = {720}, ny2[10] = {625};
            for (int i = 1; i < 4; i++) {
                nx[i] = nx[i - 1] + 115;
                nx2[i] = nx2[i - 1] + 77;
                ny[i] = ny[i - 1] - 230;
                ny2[i] = ny2[i - 1] - 133;
            }
            for (int i = 4; i < 7; i++) {
                nx[i] = nx[i - 1] + 115;
                nx2[i] = nx2[i - 1] + 77;
                ny[i] = ny[i - 1] + 230;
                ny2[i] = ny2[i - 1] + 133;
            }
            for (int i = 7; i < 10; i++) {
                nx[i] = nx[i - 1] - 172.5;
                nx2[i] = nx2[i - 1] - 115.5;
                ny[i] = ny[i - 1];
                ny2[i] = ny2[i - 1];
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
            double** T = randm(10);
            double** A = mulmr(0.95 - 5 * 0.005, T, 10);
            double** Wt = arr(10);
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    Wt[i][j] = T[i][j] * 100;
                }
            }
            double** W2t = roundm(multiply(Wt, A, 10), 10);
            print_matrix(W2t);
            double** B = matrixB(W2t, 10);
            print_matrix(B);
            double** C = matrixC(B, 10);
            double** D = matrixD(B, 10);
            double** Tr = matrixTr(10);
            double** tempMatrix = multiply(D, Tr, 10);
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    tempMatrix[i][j] += C[i][j];
                }
            }
            double** W3t = multiply(tempMatrix, W2t, 10);
            double** W = arr(10);
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    W[i][j] = W3t[i][j];
                    if (W[i][j] > 0) W[j][i] = W[i][j];
                }
            }
            printf("Matriza sumiznosti: \n");
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    if (A[i][j] == 1) A[j][i] = 1;
                }
            }
            print_matrix(A);
            printf("Matriza vag: \n");
            print_matrix(W);
            SelectObject(hdc, KPen);
            for (int i = 0; i < 10; i++) {                              //drawing
                for (int j = i; j < 10; j++) {
                    if (W[i][j] > 0) {
                        if (i == j) {                                   //if pointing on itself
                            if (i >= 0 && i < 4) {
                                Arc(hdc, nx[j], ny[j], nx[j]-40, ny[j]-40, nx[j], ny[j], nx[j], ny[j]);
                            }
                            else if (i >= 4 && i < 7) {
                                Arc(hdc, nx[j], ny[j], nx[j]+40, ny[j]-40, nx[j], ny[j], nx[j], ny[j]);
                            }
                            else {
                                Arc(hdc, nx[j], ny[j], nx[j]-40, ny[j]+40, nx[j], ny[j], nx[j], ny[j]);
                            }
                        }
                        else if (bad_targets[i][j] == 1) {
                            broken_line(nx[i], ny[i], nx[j], ny[j], 18, 55, W, i, j);    //if bad target
                        }
                        else line_to(nx[i], ny[i], nx[j], ny[j], W, i, j);
                    }
                }
            }
            SelectObject(hdc, BPen);
            for (int i = 0; i < 10; i++) {                                  //vertices
                Ellipse(hdc, nx[i] - dx, ny[i] - dy, nx[i] + dx, ny[i] + dy);
                TextOut(hdc, nx[i] - dtx, ny[i] - dy / 2, nn[i], 2);
            }
            int start, flag = 0;
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    if (W[i][j] > 0 && i != j) {
                        start = i, flag = 1;
                        break;
                    }
                }
                if (flag == 1) break;
            }
            for (int i = 0; i < 10; i++) {                                  //vertices
                Ellipse(hdc, nx2[i] - dx, ny2[i] - dy, nx2[i] + dx, ny2[i] + dy);
                TextOut(hdc, nx2[i] - dtx, ny2[i] - dy / 2, nn[i], 2);
            }
            double** resTree = arr(10);
            int visited[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            visited[start] = 1;
            double** miniSpanningTree = primAlgo(W, resTree, start, bad_targets, nx2, ny2, visited);
            printf("Matriza dereva: \n");
            print_matrix(miniSpanningTree);
            char vaga[10];
            sprintf(vaga, "Vaga: %d", veight);
            TextOut(hdc, 100, 100, vaga, 10);
            EndPaint(hWnd, &ps);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default: return(DefWindowProc(hWnd, messg, wParam, lParam));
    }
}