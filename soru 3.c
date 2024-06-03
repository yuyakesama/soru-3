/*Veri yapıları 3. Soru

Trie (veya Prefix Tree), özellikle kelimelerin saklanması ve aranması için kullanılan, ağaç benzeri bir veri yapısıdır. Bu yapı, kelimelerin ortak köklerini paylaştığı ve bu sayede bellek kullanımını optimize ettiği için oldukça etkilidir. Bir Trie veri yapısı, genellikle harflerin düğümler olarak saklandığı ve çocuk düğümlerin bir harf dizisini temsil ettiği bir ağaç yapısıdır.

Trie Yapısının Özellikleri
Kök Düğüm (Root Node): Her Trie, boş bir kök düğüm ile başlar.
Her Düğüm Bir Harf Temsil Eder: Kök düğüm hariç, her düğüm bir harfi temsil eder.
Çocuk Düğümler: Her düğümün, çocuk düğümlerine sahip olabilir, ve bu çocuk düğümler, karakterlerin devamını temsil eder.
Kelime Sonu İşareti: Her düğümde, bir kelimenin sonunu işaret eden bir işaret bulunabilir (genellikle boolean bir değerle temsil edilir).
Temel Trie İşlemleri
Ekleme (Insertion): Yeni bir kelime Trie yapısına eklenir.
Arama (Search): Bir kelimenin Trie içinde olup olmadığı kontrol edilir.
Silme (Deletion): Trie'den bir kelime silinir.
C Dilinde Trie Yapısı
Aşağıda, C dilinde basit bir Trie veri yapısının tanımı ve temel işlemleri gerçekleştiren kod örneği bulunmaktadır:

Trie Düğüm Tanımı*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26

// Trie düğüm yapısı
typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord; // Bu düğüm bir kelimenin sonunu gösterir
} TrieNode;

// Yeni bir Trie düğümü oluştur
TrieNode *createNode() {
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    node->isEndOfWord = false;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
    return node;
}
//Ekleme İşlemi
void insert(TrieNode *root, const char *key) {
    TrieNode *crawler = root;
    while (*key) {
        int index = *key - 'a';
        if (crawler->children[index] == NULL) {
            crawler->children[index] = createNode();
        }
        crawler = crawler->children[index];
        key++;
    }
    crawler->isEndOfWord = true;
}
//Arama İşlemi
bool search(TrieNode *root, const char *key) {
    TrieNode *crawler = root;
    while (*key) {
        int index = *key - 'a';
        if (crawler->children[index] == NULL) {
            return false;
        }
        crawler = crawler->children[index];
        key++;
    }
    return crawler != NULL && crawler->isEndOfWord;
}
//Silme İşlemi (Rekürsif)
bool isEmpty(TrieNode *root) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i] != NULL) {
            return false;
        }
    }
    return true;
}

TrieNode *delete(TrieNode *root, const char *key, int depth) {
    if (!root) {
        return NULL;
    }

    if (depth == strlen(key)) {
        if (root->isEndOfWord) {
            root->isEndOfWord = false;
        }
        if (isEmpty(root)) {
            free(root);
            root = NULL;
        }
        return root;
    }

    int index = key[depth] - 'a';
    root->children[index] = delete(root->children[index], key, depth + 1);

    if (isEmpty(root) && !root->isEndOfWord) {
        free(root);
        root = NULL;
    }

    return root;
}
//Kullanım Örneği
int main() {
    char keys[][8] = {"the", "a", "there", "answer", "any", "by", "bye", "their"};
    int n = sizeof(keys) / sizeof(keys[0]);

    TrieNode *root = createNode();

    // Kelimeleri ekle
    for (int i = 0; i < n; i++) {
        insert(root, keys[i]);
    }

    // Kelimeleri ara
    search(root, "the") ? printf("the -- found\n") : printf("the -- not found\n");
    search(root, "these") ? printf("these -- found\n") : printf("these -- not found\n");

    // Kelime sil
    root = delete(root, "her", 0);

    return 0;
}/*
Bu kod, temel Trie veri yapısının oluşturulması, kelime eklenmesi, aranması ve silinmesi işlemlerini göstermektedir. Trie, özellikle büyük kelime listeleriyle çalışırken etkili bir veri yapısıdır*/