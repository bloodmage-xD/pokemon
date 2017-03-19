// Example program
#include <cmath>
#include <string>
#include <iostream>
bool ispalindrome(int x ){
        int o = x;
        int a = 0;
        while (x){
                int temp = x % 10 + a * 10;
                if (temp/10 != a)
                        return 0;
        a = temp;
        x /= 10;
        }
        return a == o;

}

int main(int argc, char **argv){
        auto x = 0;
        std::cin >> x;
        long max = pow(10, x) - 1; auto  p = 0;
        long min  = max / 10;
        long max1 = pow(10,x ) - 1;
        std::cout << max << " " << min << std::endl;
        for (auto i = max1; i > max1 / 2; i--){
                for (int j = max1; j > max1 / 2; j--){
                         p = i * j;
                                if (  ispalindrome(p) && max < p)
                                        max = p;
                }
        }
        std::cout << " max is " << (int)(max % 1337);



}




