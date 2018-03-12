//
// Created by sebastian on 12.03.18.
//

#include "GreatestProduct.h"

int GreatestProduct(const std::vector<int> &numbers, int k) {

    int tab_positive[k] = {0};
    int tab_negative[k] = {0};
    int tab_negative_min[k] = {0};
    bool all_negative = true;
    int num = 1;
    int temp = 1;

    std::fill_n(tab_negative_min, k, -99999999999);

    for (int i_num : numbers) {
        if (i_num > 0) {
            all_negative = false;
            if (i_num >= tab_positive[0]) {
                tab_positive[0] = i_num;
                std::sort(tab_positive, tab_positive + k);
            }
        } else if (i_num <= 0){
            if (i_num < tab_negative[k-1]) {
                tab_negative[k - 1] = i_num;
                std::sort(tab_negative, tab_negative + k);
            }
            if (i_num >= tab_negative_min[0] || tab_negative_min[0] == 0) {
                tab_negative_min[0] = i_num;
                std::sort(tab_negative_min, tab_negative_min + k);
            }

        }
    }

    if (all_negative) {
        if (k % 2 == 0) {
            for (int i = 0; i < k; i++) {
                num *= tab_negative[i];
            }
        } else {
            for (int i = 0; i < k; i++) {
                num *= tab_negative_min[i];
            }
        }
    } else {
        num = 0;
        for (int i = k - k % 2; i >= 0; i -= 2) {
            temp = 1;
            for (int j = 0; j < i; j++) {
                temp *= tab_negative[j];
            }
            for (int j = i; j < k; j++) {
                temp *= tab_positive[j];
            }
            if (temp > num) {
                num = temp;
            }
        }
    }

    return num;
}