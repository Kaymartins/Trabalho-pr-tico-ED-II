#include <iostream>
#include <string>

using namespace std;

const int LEN = 4096;
const int MAX_LEN = 18;

// Função para compressão
string compress(string text) {
    int len = text.length();
    string compressed = "";
    int i = 0;
    while (i < len) {
        int j = i;
        int k = i + 1;
        int distance = 0;
        int length = 0;
        while (j >= 0 && k < len && text[j] == text[k]) {
            j--;
            k++;
            distance++;
            length++;
        }
        if (length > 0) {
            compressed += "(" + to_string(distance) + "," + to_string(length) + ")";
            i += length;
        } else {
            compressed += text[i];
            i++;
        }
    }
    return compressed;
}

// Função para descompressão
string decompress(string compressed) {
    string text = "";
    int len = compressed.length();
    int i = 0;
    while (i < len) {
        if (compressed[i] == '(') {
            int j = i + 1;
            while (compressed[j] != ',') {
                j++;
            }
            int distance = stoi(compressed.substr(i + 1, j - i - 1));
            int k = j + 1;
            while (compressed[k] != ')') {
                k++;
            }
            int length = stoi(compressed.substr(j + 1, k - j - 1));
            int m = text.length() - distance;
            for (int n = 0; n < length; n++) {
                text += text[m + n];
            }
            i = k + 1;
        } else {
            text += compressed[i];
            i++;
        }
    }
    return text;
}

int main() {
    string text = "aaabaaaab";
    cout << "Texto original: " << text << endl;

    string compressed = compress(text);
    cout << "Texto comprimido: " << compressed << endl;

    string decompressed = decompress(compressed);
    cout << "Texto descomprimido: " << decompressed << endl;

    return 0;
}
