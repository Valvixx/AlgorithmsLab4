#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <clocale>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* root = NULL;

struct Node* CreateTree(struct Node* root, int data) {
    if (root == NULL) {
        root = (struct Node*)malloc(sizeof(struct Node));
        if (root == NULL) {
            printf("Ошибка выделения памяти");
            exit(0);
        }
        root->left = NULL;
        root->right = NULL;
        root->data = data;
        return root;
    }

    if (data == root->data) {
        return root;  // Если элемент уже есть в дереве, ничего не делаем
    }

    if (data < root->data) {
        root->left = CreateTree(root->left, data);  // Добавляем в левое поддерево
    }
    else {
        root->right = CreateTree(root->right, data);  // Добавляем в правое поддерево
    }

    return root;
}

void print_tree(struct Node* r, int l) {
    if (r == NULL) {
        return;
    }

    print_tree(r->right, l + 1);
    for (int i = 0; i < l; i++) {
        printf(" ");
    }
    printf("%d\n", r->data);
    print_tree(r->left, l + 1);
}

struct Node* search(struct Node* root, int data) {
    if (root == NULL) {
        return NULL;  // Элемент не найден
    }

    if (root->data == data) {
        return root;  // Элемент найден
    }
    else if (data < root->data) {
        return search(root->left, data);  // Ищем в левом поддереве
    }
    else {
        return search(root->right, data);  // Ищем в правом поддереве
    }
}

int countOccurrences(struct Node* root, int data) {
    if (root == NULL) {
        return 0;  // Нет элементов в поддереве
    }

    int count = 0;
    if (root->data == data) {
        count = 1;  // Если значение найдено, увеличиваем счётчик
    }

    // Рекурсивно ищем в левом и правом поддеревьях
    count += countOccurrences(root->left, data);
    count += countOccurrences(root->right, data);

    return count;
}

int main() {
    setlocale(LC_ALL, "Russian");

    int D, start = 1;

    root = NULL;
    printf("-1 - окончание построения дерева\n");
    while (start) {
        printf("Введите число: ");
        scanf("%d", &D);
        if (D == -1) {
            printf("Построение дерева окончено\n\n");
            start = 0;
        }
        else {
            root = CreateTree(root, D);
        }
    }

    print_tree(root, 0);

    printf("Введите число для поиска: ");
    scanf("%d", &D);
    struct Node* found = search(root, D);
    if (found != NULL) {
        printf("Число %d найдено в дереве.\n", D);
    }
    else {
        printf("Число %d не найдено в дереве.\n", D);
    }

    printf("Введите число для подсчёта вхождений: ");
    scanf("%d", &D);
    int count = countOccurrences(root, D);
    printf("Число %d встречается в дереве %d раз(а).\n", D, count);

    return 0;
}
