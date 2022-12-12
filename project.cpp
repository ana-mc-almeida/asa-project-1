#include <iostream>
#include <vector>
#include <map>
using namespace std;

map<vector<int>, long long int> _possibilidades;

void print_matriz(vector<int> matriz)
{
    int n = matriz.size();
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
        _ocupacao[i] = c;
    }

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
    for (int y = 0; y < size_block; y++)
    {
        _ocupacao[i + y] -= size_block;
    }
    return _ocupacao;
}

int cabe_bloco(vector<int> _ocupacao, int i, int size)
{
    if (size == 1)
        return 1;
    size--;
    if (size + i >= (int)_ocupacao.size())
        return 0;
    for (int x = 0; x <= size; x++)
        if (_ocupacao[i + x] < _ocupacao[i])
            return 0;
    return 1;
}

int prox_vazio(vector<int> _ocupacao)
{
    int max = 0, i = 0;
    for (int x = 0; x < (int)_ocupacao.size(); x++)
    {
        if (_ocupacao[x] > max)
        {
            max = _ocupacao[x];
            i = x;
        }
    }
    return i;
}

long long int calcula_maneiras(vector<int> _ocupacao)
{
    long long int count = 0;

    if (_possibilidades.count(_ocupacao) > 0)
        return _possibilidades[_ocupacao];

    int i = prox_vazio(_ocupacao);

    if (_ocupacao[i] == 0)
        return 0;

    for (int block_size = _ocupacao[i]; block_size > 1; block_size--)
    {
        if (cabe_bloco(_ocupacao, i, block_size))
        {
            count += calcula_maneiras(coloca_quadrado(_ocupacao, i, block_size));
            count++;
        }
    }
    count += calcula_maneiras(coloca_quadrado(_ocupacao, i, 1));

    _possibilidades.insert(pair<vector<int>, long long int>(_ocupacao, count));
    return count;
}

int main()
{
    int n, m;
    long long int sum;
    vector<int> _ocupacao;

    cin >> n;
    cin >> m;

    _ocupacao = iniciar_matriz(n, m);

    sum = calcula_maneiras(_ocupacao);
    if (_ocupacao[n - 1] != 0)
        sum++;

    cout << sum << endl;
    return 0;
}
