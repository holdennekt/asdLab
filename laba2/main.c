#include <stdio.h>
#include <stdlib.h>

typedef struct linked_list {
    double info;
    struct linked_list *next;
} l_list;

l_list *l_list_init(double input_info) {
    l_list *l_p;
    l_p = malloc(sizeof(l_list));
    l_p -> info = input_info;
    l_p -> next = l_p;
    return l_p;
}

l_list *add_node(l_list *l_p, double input_info) {
    l_list *node_p, *p;
    node_p = malloc(sizeof(l_list));
    p = l_p -> next;
    l_p -> next = node_p;
    node_p -> info = input_info;
    node_p -> next = p;
    return node_p;
}

l_list *list_shift(l_list *l_p, int k) {
    for (int i = 0; i < k; i++) {
        l_p = l_p -> next;
    }
    return l_p;
}

void list_print(l_list *l_p) {
    l_list *p = l_p;
    do {
        if (l_p -> next == p) {
            printf("%.2lf %p %p\n", l_p -> info, l_p, l_p -> next);
            l_p = l_p -> next;
        }
        else {
            printf("%.2lf %p %p -> ", l_p -> info, l_p, l_p -> next);
            l_p = l_p -> next;
        }
    }
    while (l_p != p);
}

l_list *delete_head(l_list *l_p) {
    if (l_p -> next == l_p) {
        free(l_p);
        return NULL;
    }
    l_list *p = l_p -> next;
    while (p -> next != l_p) {
        p = p -> next;
    }
    p -> next = l_p -> next;
    free(l_p);
    return p -> next;
}

void delete_list(l_list *l_p) {
    while (l_p) {
        l_p = delete_head(l_p);
    }
}

int main() {
    int n, k;
    printf("input n and k\n");
    scanf("%d %d", &n, &k);
    double num;
    printf("input number(s)\n");
    scanf("%lf", &num);
    l_list *list = l_list_init(num);
    for (int i = 0; i < n - 1; i++) {
        scanf("%lf", &num);
        list = add_node(list, num);
    }
    list = list -> next;
    list = list_shift(list, k);
    list_print(list);
    delete_list(list);
}