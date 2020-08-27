#include <iostream>
#include <string>
#include <vector>

struct Phone {
    std::string Name;
    std::string Maker;
    int Price;
    int Gongsi;
    int Performance;

    bool IsGongsi;
    double Ratio;
};

int main() {
    int t;
    std::cin >> t;

    std::vector<Phone> phones(t);
    for (int i = 0; i < t; ++i) {
        Phone& phone = phones[i];
        std::cin >> phone.Name >> phone.Maker >> phone.Price >> phone.Gongsi >> phone.Performance;

        const double gongsiRatio = static_cast<double>(phone.Performance) / (phone.Price - phone.Gongsi);
        const double suntaekRatio = phone.Performance / (0.75 * phone.Price);
        if ((phone.IsGongsi = gongsiRatio > suntaekRatio)) {
            phone.Price -= phone.Gongsi;
        } else {
            phone.Price *= 0.75;
        }
        phone.Ratio = static_cast<double>(phone.Performance) / phone.Price;
    }

    int max;
    std::string want;
    std::cin >> max >> want;

    Phone* best = nullptr;
    for (Phone& phone : phones) {
        if (phone.Maker != want || phone.Price > max) continue;
        else if (best && best->Ratio < phone.Ratio || !best) {
            best = &phone;
        }
    }

    std::cout << best->Name << '\n';
    if (best->IsGongsi) {
        std::cout << "Gongsi";
    } else {
        std::cout << "Suntaek";
    }
}