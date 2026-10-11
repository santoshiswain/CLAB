
#include <stdio.h>
#include <string.h>

#define MAX 1000

typedef struct {
    char ch;
    int count;
} Node;

Node heap[30];
int hs = 0;

void swap(Node *a, Node *b) {
    Node t = *a;
    *a = *b;
    *b = t;
}

void push(char ch, int count) {
    int i = hs++;
    heap[i].ch = ch;
    heap[i].count = count;

    while (i > 0 &&
           heap[(i - 1) / 2].count < heap[i].count) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

Node pop() {
    Node result = heap[0];
    heap[0] = heap[--hs];

    int i = 0;
    while (1) {
        int l = 2 * i + 1, r = 2 * i + 2;
        int largest = i;

        if (l < hs && heap[l].count > heap[largest].count)
            largest = l;
        if (r < hs && heap[r].count > heap[largest].count)
            largest = r;

        if (largest == i)
            break;

        swap(&heap[i], &heap[largest]);
        i = largest;
    }
    return result;
}

int main() {
    char s[MAX], result[MAX];
    int k, freq[26] = {0};
    Node waiting[MAX];
    int front = 0, rear = 0, len = 0;

    printf("Enter lowercase string: ");
    scanf("%999s", s);

    printf("Enter K: ");
    scanf("%d", &k);

    int n = strlen(s);

    if (k <= 1) {
        printf("Reorganised string = %s\n", s);
        return 0;
    }

    for (int i = 0; i < n; i++)
        freq[s[i] - 'a']++;

    for (int i = 0; i < 26; i++)
        if (freq[i] > 0)
            push('a' + i, freq[i]);

    while (len < n) {
        if (hs == 0) {
            printf("Reorganised string = \"\"\n");
            return 0;
        }

        Node x = pop();
        result[len++] = x.ch;
        x.count--;

        waiting[rear++] = x;

        if (rear - front >= k) {
            Node y = waiting[front++];
            if (y.count > 0)
                push(y.ch, y.count);
        }
    }

    result[n] = '\0';
    printf("Reorganised string = %s\n", result);
    return 0;
}
