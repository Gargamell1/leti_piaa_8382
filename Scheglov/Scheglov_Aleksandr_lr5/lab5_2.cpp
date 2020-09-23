#include <iostream>
#include <map>
#include <vector>

class Vertex {
public:
    std::map<char, int> nextVertexes; // вектор вершин потомков
    std::pair<char, int> parentNode; //предок
    std::map<char, int> nextNode; //следующее ребро из вершины по какому-либо символу
    int suffixLink; //суффиксальная ссылка
    bool isTerminal; //флаг терминальной вершины
    int level; //глубина вершины
    std::vector<int> posInJokerPattern; //позиция в паттерне

    Vertex() : isTerminal(false), suffixLink(-1), level(0), parentNode(std::pair<char, int>(' ', -1)) {};
    Vertex(int prevInd, char prevChar) : isTerminal(false), suffixLink(-1), level(0), parentNode(std::pair<char, int>(prevChar, prevInd)) {};

    void printVertex() {
        if (parentNode.second != -1)


        {
            if (isTerminal) {
                std::cout << "This vertex is terminal " << std::endl;
            }
            if (!nextVertexes.empty()) {
                std::cout << "Next vertexes: ";
                for (auto& nextVertex : nextVertexes) {
                    std::cout << "(" << nextVertex.first << ", " << nextVertex.second << ") ";
                }
            }
            std::cout << std::endl;
        }
        else {
            std::cout << "Vertex is root" << std::endl;
            std::cout << "Next vertexes: ";
            for (auto& nextVertex : nextVertexes) {
                std::cout << "(\'" << nextVertex.first << "\', " << nextVertex.second << ") ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

};

class BohrWithJoker {
public:
    std::vector<Vertex> vertexes;  //все вершины бора
    char joker;  //символ джокера
    int jokerPatternSize = 0;  //размер шаблона джокера

    explicit BohrWithJoker(char joker) : joker(joker) {  //в конструкторе создаем корень и добавляем в вектор вершин
        Vertex root;
        vertexes.push_back(root);
    }

    void printBohr() {
        for (int i = 0; i < vertexes.size(); ++i) {
            std::cout << "Vertex index: " << i << std::endl;
            vertexes[i].printVertex();
        }
    }

    void addJokerPattern(std::string& jokerPattern) {  //добавление шаблона в бор
        int cur = 0;
        int counter = 0;
        bool isPrevJoker = false;
        jokerPatternSize = jokerPattern.size();
        for (int j = 0; j < jokerPattern.length(); j++) {  //проходимся по каждому символу шаблона
            if (jokerPattern[j] == joker) {  //если встретили джокер
                if (j == 0) {  //для первого символа
                    counter = 0;
                    isPrevJoker = true;
                }
                else if (isPrevJoker) { //если перед тек джокером был джокер
                    cur = 0;
                    counter = 0;
                }
                else { //делаем последний символ не джокер терминальной вершиной и добавляем в бор
                    isPrevJoker = true;
                    vertexes[cur].isTerminal = true;
                    vertexes[cur].posInJokerPattern.push_back(j - counter);
                    if (vertexes[cur].level == 0) {
                        vertexes[cur].level = counter;
                    }
                    counter = 0;
                    cur = 0;
                }
            }
            else {
                isPrevJoker = false;
                counter++;  //увеличиваем длину текущей подстроки
                if (vertexes[cur].nextVertexes.find(jokerPattern[j]) == vertexes[cur].nextVertexes.end()) {   //если нет потомка по текущему символу
                    Vertex vert(cur, jokerPattern[j]);
                    vertexes.push_back(vert);
                    vertexes[cur].nextVertexes[jokerPattern[j]] = vertexes.size() - 1;
                }
                cur = vertexes[cur].nextVertexes[jokerPattern[j]];
            }
        }
        if (!isPrevJoker) {   //если перед последним был джокер либо последний джокер
            if (vertexes[cur].level == 0) {
                vertexes[cur].level = counter;
            }
            vertexes[cur].isTerminal = true;
            vertexes[cur].posInJokerPattern.push_back(jokerPattern.length() - counter);
           }
    }

    int getSuffixLink(int i) {   //получение суффиксальной ссылки для вершины
        if (vertexes[i].suffixLink == -1) { //если еще нет суффиксальной
            if (i == 0 || vertexes[i].parentNode.second == 0) {  //если корень или его потомок, то ссылка на корень
                vertexes[i].suffixLink = 0;
            }
            else { //если нет то ищем путь из суффиксальной вершины родителя, по символу от родителя к тек вершине
                vertexes[i].suffixLink = getNextVertex(getSuffixLink(vertexes[i].parentNode.second), vertexes[i].parentNode.first);
            }
        }
        return vertexes[i].suffixLink;
    }

    int getNextVertex(int i, char c) { //следующий шаг автомата
        std::cout << "Find next move for vertex with index: " << i << " by symbol: \'" << c << "\'"<< std::endl;
        if (vertexes[i].nextNode.find(c) == vertexes[i].nextNode.end()) {  //если нет пути в словаре путей автомата по переданному сиволу
            std::cout << "No next move by symbol: \'" << c << "\'" << std::endl;
            if (vertexes[i].nextVertexes.find(c) != vertexes[i].nextVertexes.end()) { //если есть прямая ссылка
                std::cout << "There is forward move to next vertex by symbol: \'" << c << "\' to vertex with index: " << vertexes[i].nextVertexes[c] << std::endl;
                vertexes[i].nextNode[c] = vertexes[i].nextVertexes[c]; //то добавляем ее в путь
            }
            else {
                if (i == 0) {  //если корень и нет потомков с путем по переданному символу, то ссылка на корень
                    std::cout << "It is root vertex without child by symbol: \'" << c << "\' so next move is root"<< std::endl;
                    vertexes[i].nextNode[c] = 0;
                }
                else { //в противном случае добавляем в словарь след вершину из суффикасальной ссылки
                    std::cout << "Next move by suffix link" << std::endl;
                    vertexes[i].nextNode[c] = getNextVertex(getSuffixLink(i), c);
                }
            }
        }
          std::cout << "Next move vertex with index: " << vertexes[i].nextNode[c] << " by symbol \'" << c <<"\'" << std::endl;
        return vertexes[i].nextNode[c];
    }

    void findAllJokerPatternsOnText(std::string& text) {   //поиск
        std::vector<int> foundedForSymbols(text.size());
        int cur = 0;
        int numOfFoundedStr = 0;  //количество найденных подстрок
        for (auto& vertex : vertexes) {
            if (vertex.isTerminal) {
                for (int j = 0; j < vertex.posInJokerPattern.size(); j++) {
                    numOfFoundedStr++;
                }
            }
        }
        for (int i = 0; i < text.length(); i++) {  //проходимся по всем симвоалм такста
            cur = getNextVertex(cur, text[i]);  //идем по текущему символу по бору
            std::cout << std::endl<< "Current vertex index: " << cur << std::endl;
            for (int j = cur; j != 0; j = getSuffixLink(j)) {  // возвращаемся по суффиксальным в корень
                if (vertexes[j].isTerminal) {  //если нашли терминальную
                    int indInText = i + 1 - vertexes[j].level;
                    for (int k = 0; k < vertexes[j].posInJokerPattern.size(); k++) {   //по вычисленному месту текущей подстроки и добавляем в вектор числа совпадений
                        if (indInText - vertexes[j].posInJokerPattern[k] >= 0) {
                            foundedForSymbols[indInText - vertexes[j].posInJokerPattern[k]] ++;
                            std::cout << "Increase element at index: " << indInText - vertexes[j].posInJokerPattern[k] << " in array of number of matches, it's value: " << foundedForSymbols[indInText - vertexes[j].posInJokerPattern[k]] << std::endl;
                        }
                    }
                }
            }
        }
        for (int i = 0; i < foundedForSymbols.size() - jokerPatternSize + 1; i++) {  //вывод результата
            if (foundedForSymbols[i] == numOfFoundedStr) {
                std::cout << i + 1 << std::endl;
            }
        }
    }
};

int main() {
    std::string text;
    std::string jokerPattern;
    char joker;
    char c;
    std::cin >> text;
    std::cin >> jokerPattern;
    std::cin >> joker;
    BohrWithJoker bohrWithJoker(joker);
    bohrWithJoker.addJokerPattern(jokerPattern);
    bohrWithJoker.printBohr();
    bohrWithJoker.findAllJokerPatternsOnText(text);
    std::cin >> c;
}