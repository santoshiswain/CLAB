
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define NODES (2 * MAX)
#define BITS (MAX + 1)

typedef struct {
    char symbol;
    long long freq;
    int left, right;
} Node;

Node tree[NODES];
int heap[NODES];
int heapSize = 0;
int nodeCount = 0;

char symbols[MAX];
int lengths[MAX];
char codes[MAX][BITS];
int n;

/* Min-heap operations */
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void push(int x) {
    int i = ++heapSize;
    heap[i] = x;

    while (i > 1 && tree[heap[i]].freq < tree[heap[i / 2]].freq) {
        swap(&heap[i], &heap[i / 2]);
        i /= 2;
    }
}

int popMin() {
    int result = heap[1];
    heap[1] = heap[heapSize--];

    int i = 1;
    while (1) {
        int smallest = i;
        int l = 2 * i, r = 2 * i + 1;

        if (l <= heapSize &&
            tree[heap[l]].freq < tree[heap[smallest]].freq)
            smallest = l;

        if (r <= heapSize &&
            tree[heap[r]].freq < tree[heap[smallest]].freq)
            smallest = r;

        if (smallest == i)
            break;

        swap(&heap[i], &heap[smallest]);
        i = smallest;
    }

    return result;
}

int newNode(char symbol, long long freq, int left, int right) {
    int id = nodeCount++;
    tree[id].symbol = symbol;
    tree[id].freq = freq;
    tree[id].left = left;
    tree[id].right = right;
    return id;
}

/* Find the Huffman code length of each symbol */
void findLengths(int node, int depth) {
    if (tree[node].left == -1 && tree[node].right == -1) {
        for (int i = 0; i < n; i++) {
            if (symbols[i] == tree[node].symbol) {
                lengths[i] = (depth == 0) ? 1 : depth;
                return;
            }
        }
    }

    if (tree[node].left != -1)
        findLengths(tree[node].left, depth + 1);

    if (tree[node].right != -1)
        findLengths(tree[node].right, depth + 1);
}

/* Sort by length, then by symbol */
void sortSymbols() {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (lengths[i] > lengths[j] ||
               (lengths[i] == lengths[j] &&
                symbols[i] > symbols[j])) {

                int tempLen = lengths[i];
                lengths[i] = lengths[j];
                lengths[j] = tempLen;

                char tempSym = symbols[i];
                symbols[i] = symbols[j];
                symbols[j] = tempSym;
            }
        }
    }
}

/* Increment a binary code of fixed length */
void incrementCode(char *code, int len) {
    int i = len - 1;

    while (i >= 0 && code[i] == '1') {
        code[i] = '0';
        i--;
    }

    if (i >= 0)
        code[i] = '1';
}

void makeCanonicalCodes() {
    sortSymbols();

    int len = lengths[0];

    for (int i = 0; i < len; i++)
        codes[0][i] = '0';
    codes[0][len] = '\0';

    for (int i = 1; i < n; i++) {
        strcpy(codes[i], codes[i - 1]);

        incrementCode(codes[i], lengths[i - 1]);

        int oldLen = lengths[i - 1];
        int newLen = lengths[i];

        for (int j = oldLen; j < newLen; j++)
            codes[i][j] = '0';

        codes[i][newLen] = '\0';
    }
}

int main() {
    printf("Enter number of symbols (1-%d): ", MAX);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of symbols.\n");
        return 1;
    }

    printf("Enter each symbol and its positive frequency:\n");

    for (int i = 0; i < n; i++) {
        char ch;
        long long f;

        if (scanf(" %c %lld", &ch, &f) != 2 || f <= 0) {
            printf("Invalid input.\n");
            return 1;
        }

        for (int j = 0; j < i; j++) {
            if (symbols[j] == ch) {
                printf("Duplicate symbol.\n");
                return 1;
            }
        }

        symbols[i] = ch;
        lengths[i] = 0;

        int id = newNode(ch, f, -1, -1);
        push(id);
    }

    /* Construct Huffman tree */
    while (heapSize > 1) {
        int left = popMin();
        int right = popMin();

        long long sum = tree[left].freq + tree[right].freq;

        int parent = newNode('\0', sum, left, right);
        push(parent);
    }

    int root = popMin();

    findLengths(root, 0);
    makeCanonicalCodes();

    printf("\nCanonical Huffman Codebook:\n");
    printf("Symbol\tFrequency\tLength\tCode\n");

    for (int i = 0; i < n; i++) {
        long long freq = 0;

        /* Find the original frequency */
        for (int j = 0; j < nodeCount; j++) {
            if (tree[j].left == -1 && tree[j].right == -1 &&
                tree[j].symbol == symbols[i]) {
                freq = tree[j].freq;
                break;
            }
        }

        printf("%c\t%lld\t\t%d\t%s\n",
               symbols[i], freq, lengths[i], codes[i]);
    }

    return 0;
}