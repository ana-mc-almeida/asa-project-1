#include <iostream>
#include <vector>
#include <map>
// #include <list>
using namespace std;

void print_matriz(vector<vector<int>> matriz)
{
    int n = matriz.size();
    // cout << "n=" << n << endl;
    for (int i = 0; i < n; i++)
    {
        int m = matriz[i].size();
        // cout << "m=" << m << endl;
        for (int j = 0; j < m; j++)
            cout << matriz[i][j] << " ";
        cout << endl;
    }
}

vector<vector<int>> iniciar_matriz(const int n, const int m)
{
    int c;
    vector<vector<int>> _ocupacao;

    _ocupacao.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> c;
        // cout << "c=" << c << endl;
        _ocupacao[i].resize(m);
        for (int j = 0; j < c; j++)
            _ocupacao[i][j] = 1;
        for (int j = c; j < m; j++)
            _ocupacao[i][j] = 0;
    }

    // print_matriz(_ocupacao);
    return _ocupacao;
}

int cabe_bloco(vector<vector<int>> _ocupacao, int i, int j, int size)
{
    if (size == 1)
        return 1;
    size--;
    if (i + size >= (int)_ocupacao.size() || j + size >= (int)_ocupacao[i].size())
        return 0;
    for (int y = j; y < j + size; y++)
        if (!_ocupacao[i][y])
            return 0;
    return _ocupacao[i][j + size] && _ocupacao[i + size][j + size] && _ocupacao[i + size][j];
}

vector<vector<int>> coloca_quadrado(vector<vector<int>> _ocupacao, int i, int j, int size)
{
    // cout << "COLOCA QUADRADO:\n";
    vector<vector<int>> aux = _ocupacao;
    for (int x = i; x < i + size; x++)
    {
        for (int y = j; y < j + size; y++)
            aux[x][y] = 0;
    }
    // print_matriz(aux);
    // cout << endl;
    return aux;
}

int calcula_maneiras(vector<vector<int>> _ocupacao, int start_i, int start_j)
{
    // cout << "--------ENTREI NO CALCULA COM (" << start_i << "," << start_j << ")" << endl;
    // cout << "matriz inicial: \n";
    // print_matriz(_ocupacao);
    // cout << endl;

    int max_j = _ocupacao[start_i].size();
    int count = 0, max_block;
    int so_para_teste = 0;

    if (start_j >= max_j)
    {
        start_j = 0;
        start_i++;
    }

    if (start_i > (int)_ocupacao.size() - 1)
        return 0;

    while (!_ocupacao[start_i][start_j])
    {
        start_j++;
        if (start_j == max_j)
        {
            start_j = 0;
            start_i++;
        }
        if (start_i >= (int)_ocupacao.size() - 1 && start_j >= max_j - 1)
            return 0;
        // cout << "preso no while com i= " << start_i << " e j= " << start_j << endl;
    }

    // cout << "AVALIDAR O PONTO (" << start_i << "," << start_j << ")" << endl;
    max_block = max_j - start_j;

    for (int block_size = max_block; block_size > 0; block_size--)
    {
        if (cabe_bloco(_ocupacao, start_i, start_j, block_size))
        {
            // cout << "Cabe bloco de " << block_size << " por " << block_size << endl;
            so_para_teste = calcula_maneiras(coloca_quadrado(_ocupacao, start_i, start_j, block_size), start_i, start_j);
            // cout << "so para teste = " << so_para_teste << endl;
            count += so_para_teste;
            if (block_size > 1)
                count++;
            // cout << "sum=" << sum << endl;
            // cout << "count=" << count << endl;
        }
    }
    // sum += count;
    // sum += count;
    // cout << "-----count=" << count << endl;
    // cout << "--------SAI DO CALCULA NO PONTO (" << start_i << "," << start_j << ")\n"
    //  << endl;

    // cout << "-----sum=" << sum << endl;
    return count;
}

int main()
{
    int n, m, sum;
    // vector<vector<int>> _ocupacao{{0, 0, 0}, {1, 1, 1}, {1, 1, 1}};
    vector<vector<int>> _ocupacao;
    map<vector<int>, int> _possibilidades;

    _possibilidades.insert(pair<vector<int>, int>({2, 2}, 1));

    cin >> n;
    cin >> m;
    // cout << "Ladrilho de " << n << " por " << m << endl;

    _ocupacao = iniciar_matriz(n, m);

    // cout << cabe_bloco(0, 0, 2) << endl;
    // cout << cabe_bloco(0, 2, 3) << endl;
    // cout << cabe_bloco(2, 1, 2) << endl;
    // cout << cabe_bloco(0, 1, 3) << endl;
    // cout <<  cabe_bloco(_ocupacao, 1, 0, 2);

    sum = calcula_maneiras(_ocupacao, 0, 0);
    if (_ocupacao.back()[0] != 0)
        sum++;

    cout << sum << endl;
    return 0;
}