#include <iostream>
#include <vector>
#include <map>
// #include <list>
using namespace std;

map<vector<int>, long long int> _possibilidades;

void print_matriz(vector<int> matriz)
{
    int n = matriz.size();
    // cout << "n=" << n << endl;
    cout << "Matriz = (";
    for (int i = 0; i < n; i++)
    {
        cout << matriz[i] << " ";
    }
    cout << " )" << endl;
}

vector<int> iniciar_matriz(const int n, const int m)
{
    int c;
    vector<int> _ocupacao;

    _ocupacao.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> c;
        // cout << "c=" << c << endl;
        _ocupacao[i] = c;
    }

    // print_matriz(_ocupacao);
    return _ocupacao;
}

void limpa_matriz(vector<int> _ocupacao)
{
    for (int i = 0; i < (int)_ocupacao.size(); i++)
    {
        if (_ocupacao[i] == 1)
            _ocupacao[i] = 0;
    }
}

vector<int> coloca_quadrado(vector<int> _ocupacao, int i, int size_block)
{
    // cout << "COLOCA QUADRADO\n";
    // print_matriz(_ocupacao);
    // cout << "size_block=" << size_block << endl;
    // cout << "i=" << i << endl;
    for (int y = 0; y < size_block; y++)
    {
        _ocupacao[i + y] -= size_block;
    }
    // print_matriz(_ocupacao);
    return _ocupacao;
}

int cabe_bloco(vector<int> _ocupacao, int i, int size)
{
    // cout << "CABE BLOCO\n size=" << size << endl;
    if (size == 1)
        return 1;
    size--;
    if (size + i >= (int)_ocupacao.size())
        return 0;
    for (int x = 0; x <= size; x++)
        if (_ocupacao[i + x] < _ocupacao[i])
            return 0;
    return 1;
    // return _ocupacao[i][j + size] && _ocupacao[i + size][j + size] && _ocupacao[i + size][j];
}

int prox_vazio(vector<int> _ocupacao)
{
    // cout << "PROX VAZIO\n";
    // print_matriz(_ocupacao);
    // // while (_ocupacao[i] == 0 && i < (int)_ocupacao.size())
    // //     i++;
    // // cout << "sai--- com i=" << i << endl;
    // // return i;
    // if (i >= (int)_ocupacao.size())
    //     // while (_ocupacao[i] == 0)
    //     i = 0;
    // return i;
    int max = 0, i = 0;
    for (int x = 0; x < (int)_ocupacao.size(); x++)
    {
        if (_ocupacao[x] > max)
        {
            max = _ocupacao[x];
            i = x;
        }
    }
    // cout << "---i-- = " << i << endl;
    return i;
}

long long int calcula_maneiras(vector<int> _ocupacao)
{
    // cout << "ENTREI CALCULA MANEIRAS\n";
    // print_matriz(_ocupacao);

    long long int count = 0;

    if (_possibilidades.count(_ocupacao) > 0)
    {
        // cout << "*++------Cromos repetidos não completam cadernetas++++++\n";
        return _possibilidades[_ocupacao];
    }

    int i = prox_vazio(_ocupacao);

    if (_ocupacao[i] == 0)
    {
        // cout << "vou sair\n";
        return 0;
    }

    // cout << "i=" << i << endl;

    for (int block_size = _ocupacao[i]; block_size > 1; block_size--)
    {
        if (cabe_bloco(_ocupacao, i, block_size))
        {
            count += calcula_maneiras(coloca_quadrado(_ocupacao, i, block_size));
            count++;
        }
    }
    count += calcula_maneiras(coloca_quadrado(_ocupacao, i, 1));

    // cout << "saí calcula maneiras com count=" << count << "e matriz = ";
    // print_matriz(_ocupacao);
    _possibilidades.insert(pair<vector<int>, long long int>(_ocupacao, count));
    return count;
}

int main()
{
    int n, m;
    long long int sum;
    // vector<vector<int>> _ocupacao{{0, 0, 0}, {1, 1, 1}, {1, 1, 1}};
    vector<int> _ocupacao;
    // map<vector<int>, int> _possibilidades;

    // _possibilidades.insert(pair<vector<int>, int>({2, 2}, 1));

    cin >> n;
    cin >> m;
    // cout << "Ladrilho de " << n << " por " << m << endl;

    _ocupacao = iniciar_matriz(n, m);
    // print_matriz(_ocupacao);

    sum = calcula_maneiras(_ocupacao);
    if (_ocupacao[n - 1] != 0)
        sum++;

    cout << sum << endl;
    return 0;
}

// vector<vector<int>> coloca_quadrado(vector<int> _ocupacao, int i, int j, int size)
// {
//     // cout << "COLOCA QUADRADO:\n";
//     vector<vector<int>> aux = _ocupacao;
//     for (int x = i; x < i + size; x++)
//     {
//         for (int y = j; y < j + size; y++)
//             aux[x][y] = 0;
//     }
//     // print_matriz(aux);
//     // cout << endl;
//     return aux;
// }

// int calcula_maneiras(vector<int> _ocupacao, int start_i, int start_j)
// {
//     // cout << "--------ENTREI NO CALCULA COM (" << start_i << "," << start_j << ")" << endl;
//     // cout << "matriz inicial: \n";
//     // print_matriz(_ocupacao);
//     // cout << endl;

//     int max_j = _ocupacao[start_i].size();
//     int count = 0, max_block;
//     int so_para_teste = 0;

//     if (start_j >= max_j)
//     {
//         start_j = 0;
//         start_i++;
//     }

//     if (start_i > (int)_ocupacao.size() - 1)
//         return 0;

//     while (!_ocupacao[start_i][start_j])
//     {
//         start_j++;
//         if (start_j == max_j)
//         {
//             start_j = 0;
//             start_i++;
//         }
//         if (start_i >= (int)_ocupacao.size() - 1 && start_j >= max_j - 1)
//             return 0;
//         // cout << "preso no while com i= " << start_i << " e j= " << start_j << endl;
//     }

//     // cout << "AVALIDAR O PONTO (" << start_i << "," << start_j << ")" << endl;
//     max_block = max_j - start_j;

//     for (int block_size = max_block; block_size > 0; block_size--)
//     {
//         if (cabe_bloco(_ocupacao, start_i, start_j, block_size))
//         {
//             // cout << "Cabe bloco de " << block_size << " por " << block_size << endl;
//             so_para_teste = calcula_maneiras(coloca_quadrado(_ocupacao, start_i, start_j, block_size), start_i, start_j);
//             // cout << "so para teste = " << so_para_teste << endl;
//             count += so_para_teste;
//             if (block_size > 1)
//                 count++;
//             // cout << "sum=" << sum << endl;
//             // cout << "count=" << count << endl;
//         }
//     }
//     // sum += count;
//     // sum += count;
//     // cout << "-----count=" << count << endl;
//     // cout << "--------SAI DO CALCULA NO PONTO (" << start_i << "," << start_j << ")\n"
//     //  << endl;

//     // cout << "-----sum=" << sum << endl;
//     return count;
// }