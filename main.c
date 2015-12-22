#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct IP {
    u8 first;
    u8 second;
    u8 third;
    u8 fourth;
} IP;

typedef struct Interval {
    u32 low;
    u32 high;
} Interval;

typedef struct Node {
    Interval i;
    u32 max;
    const char *owner;
    struct Node *left;
    struct Node *right;
} Node;

u32 toU32(const IP t_ip) {
    u32 t_num = (t_ip.first << (sizeof(u8) * 8 * 3)) +
                (t_ip.second << (sizeof(u8) * 8 * 2)) +
                (t_ip.third << (sizeof(u8) * 8)) +
                t_ip.fourth;
    return t_num;
}

IP toIP(const u32 val) {
    IP t_ip;
    t_ip.first = val >> (sizeof(u8) * 8 * 3);
    t_ip.second = val >> (sizeof(u8) * 8 * 2);
    t_ip.third = val >> (sizeof(u8) * 8);
    t_ip.fourth = val;
    return t_ip;
}

Node *newNode(Interval i, const char *owner) {
    Node *tmp = malloc(sizeof(Node));
    tmp->i = i;
    tmp->max = i.high;
    tmp->owner = owner;
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
}

Node *insert(Node *root, Interval i, const char *owner) {
    if (root == NULL)
        return newNode(i, owner);

    u32 l = root->i.low;

    if (i.low < l) {
        root->left = insert(root, i, owner);
    } else {
        root->right = insert(root, i, owner);
    }

    if (root->max < i.high) {
        root->max = i.high;
    }

    return root;
}

int main() {
    IP t_ip;
    t_ip.first = 127;
    t_ip.second = 0;
    t_ip.third = 0;
    t_ip.fourth = 1;
    u32 val = 2130706433;
    IP t_ip2 = toIP(val);

    printf("IP %d.%d.%d.%d: %d\n", t_ip.first, t_ip.second, t_ip.third, t_ip.fourth, toU32(t_ip));
    printf("%d: IP %d.%d.%d.%d\n", val, t_ip2.first, t_ip2.second, t_ip2.third, t_ip2.fourth);

    Interval i;
    i.high = 2130706433;
    i.low = 2130706432;
    char *owner = "Carp incorporated";
    Node *tree = insert(NULL, i, owner);

    return 0;
}
