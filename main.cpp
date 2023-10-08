#include <iostream>
#include <windows.h>
#include <locale.h>
using namespace std;

struct House {
int entrances;
int* floors;
int apartaments_per_floor;
bool first_free;
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

        cout << "Программа определяет по номеру квартиры в каком подъезде"
        << " и на каком этаже она находится.\n" << endl;

        House building;

        cout << "Введите необходимую для расчетов информацию о доме:\n";
        cout << "Введите количество подъездов в доме:";
        cin >> building.entrances;

        char yn;
        cout << "Все подъезды имеют одинаковое количество этажей(д/н):";
        cin >> yn;

        int floors_count;
        building.floors = new int[building.entrances];

        if(yn == 'д') {
            cout << "Введите количество этажей в доме: ";
            cin >> floors_count;
            for (int i=0; i < building.entrances; i++)
                building.floors[i] = floors_count;
        } else {
            for(int i=0; i<building.entrances; i++) {
                cout << "Введите количество этажей для " << i + 1 << " -го подъезда: ";
                cin >> building.floors[i];
           }
        }

        cout << "На первом этаже есть квартиры? (д/н): ";
        cin >> yn;

        if(yn = 'д') {
            building.first_free = false;
        } else building.first_free = true;

        cout << "Введите количество квартир на этаже: ";
        cin >> building.apartaments_per_floor;

        int apartament_number;
        cout << "Введите номер квартиры: ";
        cin >> apartament_number;

        int reply_number = 0;
        int apartaments_in_house = 0;
        int prevous_aih = 0;
        int entrance = 0;
        int floor = 0;

        if(apartament_number >0) {
            for(int i = 0; i < building.entrances; i++){
                if(building.first_free) {
                    apartaments_in_house += (building.floors[i] - 1) * building.apartaments_per_floor;
                } else {
                  apartaments_in_house += building.floors[i] * building.apartaments_per_floor;
                }
                if ((prevous_aih < apartament_number) && (apartament_number <= apartaments_in_house)) {
                    entrance = i+1;
                    int aie = apartament_number - prevous_aih;
                    floor = (aie-1) / building.apartaments_per_floor + 1;
                    if(building.first_free) floor++;
                }
                prevous_aih = apartaments_in_house;
            }
            if(apartament_number > apartaments_in_house) reply_number=2;
        } else reply_number = 1;

const char* err_desc[2] {
    "Введен недействительный номер квартиры." , "Квартиры с таким номером нет в данном доме."
 };
 cout << endl << "В описанном вами доме " << apartaments_in_house << " квартир: \n";
 if (reply_number == 0) {
    cout << "Квартира №" << apartament_number << " находится в " << entrance << " подъезде, "
    "на " << floor << " этаже.";
 } else {
 cout << err_desc[reply_number-1];
 }

 delete [] building.floors;

 cout << endl << "\nДля выхода нажмите <Enter>..";
 fflush(stdin);
 cin.get();
 return 0;
}
