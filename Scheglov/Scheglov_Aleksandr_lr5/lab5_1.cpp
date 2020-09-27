#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

class Vertex {
public:
    std::map<char, int> nextVertexes; // вектор вершин потомков
    std::pair<char, int> parentNode; //предок
    std::map<char, int> nextNode; //следующее ребро из вершины по какому-либо символу
    int suffixLink; //суффиксальная ссылка
    bool isTerminal; //флаг терминальной вершины
    int level; //уровень вершины
    std::vector<int> numbers; //номера паттернов

    Vertex() : isTerminal(false), suffixLink(-1), level(0), parentNode(std::pair<char, int>(' ', -1)) {};
    Vertex(int prevInd, char prevChar) : isTerminal(false), suffixLink(-1), level(0), parentNode(std::pair<char, int>(prevChar, prevInd)) {};

    void printVertex() {
        if (parentNode.second != -1)
        {
            if (isTerminal) {
                std::cout <<"This vertex is terminal "<< std::endl;
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
               for(auto & nextVertex : nextVertexes) {
                   std::cout << "(\'" << nextVertex.first << "\', " << nextVertex.second << ") ";
               }
               std::cout << std::endl;
        }
          std::cout << std::endl;
    }
};

class Bohr {
public:
    std::vector<std::pair<int, int>> result;  //результирующий вектор
    std::vector<Vertex> vertexes; //вершины дерева
    int terminalsNumb; //количество терминальных
    int mostDeepLevel; //самая длинная цепочка прямых ссылок
    Bohr() {
        Vertex root; //создаем корень и добавляем ввектор, а также остальные инициализируем поля
        vertexes.push_back(root);
        terminalsNumb = 0;
        mostDeepLevel = 0;
    }

    void addStringToBohr(const std::string& str) {  //добавление строки в бор
        int cur = 0;   //тек. на начало
        for (char i : str) {  //проходимся по всем символам переданной строки
            if (vertexes[cur].nextVertexes.find(i) == vertexes[cur].nextVertexes.end()) {  //если в боре нет такой вершины
                Vertex curVertex(cur, i);  //создаем ее и добавляем
                vertexes.push_back(curVertex);
                vertexes[cur].nextVertexes[i] = vertexes.size() - 1; //связываем потомка с родителем
            }
            cur = vertexes[cur].nextVertexes[i]; //если в боре уже есть такая вершина, просто переходим дальше
        }
        vertexes[cur].isTerminal = true;  //последняя вершина терминальная
        vertexes[cur].numbers.push_back(terminalsNumb++); //добавляем номер шаблона данной вершины
        vertexes[cur].level = str.length();
        if (str.length() > mostDeepLevel) {
            mostDeepLevel = str.length(); //изменяем длину самой длинной цепочки прямых ссылок
        }
    }

    void printBohr() {
        for (int i = 0; i < vertexes.size(); ++i) {
              std::cout << "Vertex index: " << i << std::endl;
            vertexes[i].printVertex();
        }
    }

    int getSuffixLink(int i) {   //получение суффиксальной ссылки для вершины
        if (vertexes[i].suffixLink == -1) { //если еще нет суффиксальной
            if (i == 0 || vertexes[i].parentNode.second == 0) {  //если корень или его потомок, то ссылка на корень
                vertexes[i].suffixLink = 0;
            }
            else { //если нет то ищем путь из суффиксальной вершины родителя, по символу от родителя к текущей вершине
                vertexes[i].suffixLink = getNextVertex(getSuffixLink(vertexes[i].parentNode.second), vertexes[i].parentNode.first);
            }
        }
        return vertexes[i].suffixLink;
    }

    int getNextVertex(int i, char c) { //следующий шаг автомата
        std::cout <<std::endl<< "Find next move for vertex with index: " << i << " by symbol: \'" << c << "\'"<< std::endl;
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
                    std::cout << "Next move by suffix link" << std::endl <<"{" << std::endl;
                    vertexes[i].nextNode[c] = getNextVertex(getSuffixLink(i), c);
                    std::cout << "}" << std::endl;
                }
            }
        }
          std::cout << "Next move vertex with index: " << vertexes[i].nextNode[c] << " by symbol \'" << c <<"\'" << std::endl;
        return vertexes[i].nextNode[c];
    }

    void findAllPatternsOnText(std::string& text) { //поиск
        int cur = 0; // текущая равна корню
        std::cout << "Start from root" << std::endl;
        for (int i = 0; i < text.length(); i++) {
            cur = getNextVertex(cur, text[i]);  //получаем путь по i - ому символу текста
            std::cout << "Start finding terminal vertexes by suffix links: " << std::endl<<"["<<std::endl;
            for (int j = cur; j != 0; j = getSuffixLink(j)) {  // затем проходимся от текущего символа до корня по суффиксальным
                if (vertexes[j].isTerminal) { //если нашли терминальную
                    for (int k = 0; k < vertexes[j].numbers.size(); k++) {  //то добавляем в результат найденный паттерн, а если есть одинаковые паттерны, то добаляем в результат все
                        std::pair<int, int> res(vertexes[j].numbers[k], i + 2 - vertexes[j].level);
                        result.push_back(res);
                    }
                }
            }
            std::cout <<"]"<<std::endl << "Next current is vertex with index: " << cur << std::endl;
        }
        sort(result.begin(), result.end(), compare);   //сортировка результата
        int mostSuffixChain = 1;
        int mostCompSuffixChain = 0;
        std::cout << "Search longest compressed and suffix link chain" << std::endl;
        for (int i = 1; i < vertexes.size(); i++) {  //проходимся по каждой вершине бора
            int curSuffixChain = 1;
            int curCompSuffixChain = 0;
            int curVertex = i;
            int flag = 1;
            std::cout << "Start from index = "<<curVertex << std::endl;
            while (vertexes[curVertex].suffixLink != 0 ) {  //из каждой вершины проходимся по суффиксальным и считаем длину суф цепи
                curSuffixChain++;
                curVertex = getSuffixLink(curVertex);
                std::cout << "Now in index = " << curVertex << std::endl;
                if (vertexes[curVertex].isTerminal && flag == 1)
                {
                    curCompSuffixChain++;
                }
                else
                {
                    flag = 0;
                }
            }
            if (curCompSuffixChain > mostCompSuffixChain) {
                mostCompSuffixChain = curCompSuffixChain;
            }
            if (curSuffixChain > mostSuffixChain) {
                mostSuffixChain = curSuffixChain;
            }
        }
        if (!result.empty()) 
        {
            std::cout << "Result: " << std::endl;
            std::cout << "Index in text | pattern number" << std::endl;
            for (auto& i : result) {    //выводим каждую пару результата
                std::cout << i.second << " " << i.first + 1 << std::endl;
            }
        }
        else
        {
            std::cout << "Patterns not founded in text" << std::endl;
        }
        std::cout << "Longest compressed suffix link chain: " << mostCompSuffixChain << std::endl;  //выводим максимальную цепочку прямых ссылок
        std::cout << "Longest suffix link chain: " << mostSuffixChain << std::endl;

    }

    static int compare(std::pair<int, int> a, std::pair<int, int> b) {  //компаратор пар для ответа
        if (a.second == b.second) {
            return a.first < b.first;
        }
        else {
            return a.second < b.second;
        }
    }
};

int main() {
    std::string text;
    std::string curPattern;
    int size = 0;
    char c;
    std::cin >> text;
    std::cin >> size;
    Bohr bohr;
    for (int i = 0; i < size; ++i) {
        std::cin >> curPattern;
        bohr.addStringToBohr(curPattern);
    }
    bohr.printBohr();
    bohr.findAllPatternsOnText(text);
    std::cin >> c;
}