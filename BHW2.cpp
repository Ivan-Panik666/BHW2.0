#include<iostream>
#include<vector>
#include<string>
#include <initializer_list>
#include <windows.h>
using namespace std;

class ListDable;

class People
{
public:
	People(const initializer_list<string>& basket_temp) {

		next = nullptr;
		prev = nullptr;

		for (auto it = basket_temp.begin(); it != basket_temp.end(); ++it) {
			korzina.push_back(*it);
		}
		vozrast = 1 + rand() % 42;
	};
	~People() {};
	friend class ListDable;
	void print() const;
	void add(const string& prodykt);
	
	
	string get_product()
	{
		if (!korzina.empty())
		{
			string product = korzina.back();
			korzina.pop_back();
			return product;
		}
		else
		{
			return "eptu";
		}
	}
	int get_vozrast() 
	{
		return vozrast;
	}



private:
	std::vector<string> korzina; 
	People* next;
	People* prev;
	int vozrast;
};

void People::add(const string& prodykt) 
{
	korzina.push_back(prodykt);
}
void People::print() const
{
	int size;
	size = korzina.size();
	std::cout << "korzina:";
	for (unsigned i = 0; i < size; ++i)
		std::cout << ' ' << korzina[i];
	std::cout << '\n';
};


class ListDable
{
private:
	People* head;
	People* tail;
	int saiz;
	static int const max_size = 2;
public:
	ListDable();
	~ListDable() { 
		People* oplachi = head;
		while (oplachi != NULL) {
			People* sled_oplat = oplachi->next;
			delete oplachi;
			oplachi = sled_oplat;

		}
	};
	void push_back(People* people)
	{
		if (people == nullptr) {
			throw std::invalid_argument("Cannot add nullptr to the list.");
		}

		people->next = NULL;

		if (head == NULL && tail == NULL)
		{
			head = people;
			tail = people;
			//people->next = NULL;
			people->prev = nullptr; // Set prev to nullptr
		}
		else
		{
			people->prev = tail;
			//people->next = NULL;
			tail->next = people;
			tail = people;
		}
		saiz++;
	}
	void print() const
	{
		if (0 == saiz)
		{
			cout << "Очередь Пуста" << endl;
		}
		People* corent = head;
		while (corent != NULL)
		{
			corent->print();
			corent = corent->next;
		}
	};
	
	void pop_front()
	{
		People* cur = head;//удалять из головы очереди
		head = head->next;
		delete cur;	
		if (head != NULL)
		{
			head->prev = NULL;//Перед головой никого нет
		}
		saiz--;
	}

	static int get_max_size()
	{
		return max_size;
	}

	bool empty() {
		return head == nullptr;
	}
	int get_size() const
	{
		return saiz;
	}
	//возвращать человека во главе очереди с его корзинкой
	People* front()
	{
		return head;
	}

};

ListDable::ListDable()
{
	cout << "Касса открыта" << endl;
	saiz = 0;
	head = NULL;
	tail = NULL;
}


int main()
{
	setlocale(LC_ALL, "ru");
	// получит с консоли кол-во касс
	cout << "Введите количество касс: " << endl;
	size_t count_checkout;
	cin >> count_checkout;
	// получить число покупателей 
	cout << "Введите количество покупателей: " << endl;
	size_t count_buyers;
	cin >> count_buyers;

	int max_ochered = ListDable::get_max_size();
	ListDable* kassa = new ListDable[count_checkout];
	
	//ассоримент
	vector<string> in_magazine = { "water", "ice", "vodka" };
	unsigned int seed = in_magazine.size();
	// пока все покупатели не купят товары, до 0 покупателей.

	for (int b = count_buyers; b != 0;)
	{
		cout << "Покупатель " << b << endl;
		int cur_b = b;//кол-во людей перед кассой
		//для каждой свободной кассы сгенерировать макс 
		for (int k = count_checkout - 1; k >= 0; k--)
		{
			if (kassa[k].empty())
			{
				cout << "Пустая касса № " << k << endl;
			}
			else if (kassa[k].get_size() < kassa[k].get_max_size())
			{
				cout << "Есть место у кассы № " << k << endl;
			}
			else
			{
				cout << "Касса занята " << k << endl;
				continue;
			}
			//беру очередь1, добавляю макс колво покупателей
			srand(seed);
			int ind = 0 + rand() % seed;
			int ind2 = 0 + rand() % seed;
			if (cur_b > 0)
			{
				kassa[k].push_back(new People{
				in_magazine[ind], in_magazine[ind2]
					});
				cur_b--;
				cout << "Положил в корзину: " << in_magazine[ind] << " " << in_magazine[ind2] << endl;
			}
			else
			{
				cout << " Некого ставить в очередь " << b << endl;			
				break;
			}
		}
		//исли каксса не пустая то отпускаем 1 клиента	
		for (int k = count_checkout - 1; k >= 0; k--)
		{
			if (kassa[k].empty()) 
			{
				cout << "Касса без очереди: " << k << endl;
			}
			else
			{
				cout << "Покупатель стоит на кассе " << k << endl;
				while (true) // пикаем товары с ленты 
				{
					string pruduct = kassa[k].front()->get_product();
					cout << "Покупатель купил: " << pruduct << endl;
					if (pruduct != "eptu")
					{
						cout << "ПИК " << pruduct << endl;
						int pause = 1 + rand() % 6; // пауза от 3 до 11 включ
						Sleep(1000 * pause);



						if (kassa[k].front()->get_vozrast() < 18 and pruduct == "vodka")
						{
							cout << "ГААААААЛЯЯЯЯЯ ОТМЕНА!" << k << endl;
							int pause = 4 + rand() % 5; // пауза от 3 до 11 включ
							Sleep(1000 * pause);
						}
					
					}
					else
					{
						break;
					}
				}
				b--;
			}
		}
	}

	delete[]kassa;
	return 0;

	People Ivan({});
	Ivan.add("MILK");
	Ivan.add("ICE");
	Ivan.print();
	ListDable Kassa1;
	Kassa1.print();
	Kassa1.push_back(new People({ "Milk", "oil" }));
	Kassa1.print();
	Kassa1.pop_front();
	Kassa1.print();



}
//удаление и случайная задержка

//В магазин заходит от 5 от 15 клиентов. Затем они подходят к кассе и их начинают обслуживать по правилу FIFO со случайной задержкой
//от 1 секунды до 3 секунд - в это время пробивается от 1 до 15 ед.товаров.
//Количество клиентов и касс задает игрок, может задать рандомно и может через пользовательский ввод.
