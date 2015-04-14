#include <constream>
using namespace conio;
using namespace std;

int main() {
    int i;

    cout << setcrsrtype(_SOLIDCURSOR);
    cout << "fgjdfgdfklgjkldfjl";
    cin >> i;
    
    cout << clrscr << setcrsrtype(_NORMALCURSOR);

    cin >> i;
    
    cout << setattr(YELLOW) << setxy(10, 10) << "Aaa";
    
    cout << normvideo;
    return 0;
}

