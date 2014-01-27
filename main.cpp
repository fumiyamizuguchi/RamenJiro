//
//  main.cpp
//  RamenJiro(ラーメン二郎巡回問題)
//
//  Created by 水口 史椰 on 2013/12/27.
//  Copyright (c) 2013年 edu.self. All rights reserved.
//

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 38
#define NUM_OF_GENES 12

//店舗のデータを格納するオブジェクトのクラス定義
class shops
{
private:
    float x;
    float y;
    char name[40];
public:
    void set_x(float x);
    void set_y(float y);
    void set_name(char *name);
    float get_x();
    float get_y();
    char* get_name();
};

//shopsクラスのメソッド定義
void shops::set_x(float _x) {
    x = _x;
}
void shops::set_y(float _y) {
    y = _y;
}
void shops::set_name(char *_name) {
    strcpy(name, _name);
}
float shops::get_x() {
    return x;
}
float shops::get_y() {
    return y;
}
char* shops::get_name() {
    return name;
}

//各店舗のデータを格納するshopsクラスのインスタンス生成
shops shop[SIZE];


////ランダムに巡回ルートを作成する関数
void makeRoute(int *gene);
//２店舗間の距離を返す関数
float getDistance(shops *shop1, shops *shop2);
//巡回ルートの合計距離を返す関数
float getTotalDistance(int *gene);
//遺伝子同士を交配する関数
void getNextGeneration(int (*genes)[SIZE]);

int main(void)
{
    printf("ラーメン二郎全店を巡回する最短ルートを探索しています...\n");
    //二郎全店舗名を入力する配列
    char names[SIZE][40] = {"三田本店", "目黒店", "品川店", "新橋店", "神田神保町店", "亀戸店", "環七一之江店", "小岩店", "千住大橋駅前店", "赤羽店", "西台駅前店", "桜台駅前店", "荻窪店", "環七新代田店", "上野毛店", "新宿小滝橋通り店", "歌舞伎町店", "池袋東口店", "仙川店", "ひばりヶ丘駅前店", "新小金井街道店", "府中店", "立川店", "八王子野猿街道店２", "めじろ台法政大学前店", "京急川崎店", "鶴見店", "横浜関内店", "中山駅前店", "相模大野店", "湘南藤沢店", "松戸駅前店", "京成大久保店", "茨城守谷店", "大宮店", "栃木街道店", "仙台店", "札幌店"};
    //各店舗のx座標
    float cordinates_x[SIZE] = {35.6480801, 35.6341918, 35.6238941, 35.6656255, 35.6963775, 35.7019335, 35.6840881, 35.7349536, 35.7425936, 35.7798005, 35.7868841, 35.7388065, 35.7035931, 35.6619732, 35.612421, 35.6964591, 35.6957565, 35.7282785, 35.6617852, 35.7500101, 35.7084359, 35.6720481, 35.6965106, 35.6295148, 35.6294833, 35.5349024, 35.4970884, 35.4421385, 35.5130707, 35.5299308, 35.3429086, 35.7860021, 35.6914847, 35.9240496, 35.9034403, 36.4236329, 38.26171009999999, 43.0673949};
    //各店舗のy座標
    float cordinates_y[SIZE] = {139.74161430000004, 139.70705120000002, 139.74299569999994, 139.75057130000005, 139.75646989999996, 139.82667820000006, 139.88195110000004, 139.88001039999995, 139.7970037, 139.72084730000006, 139.6748096, 139.66185940000003, 139.62628870000003, 139.66042670000002, 139.63897769999994, 139.69845810000004, 139.70192450000002, 139.7138357, 139.58388289999994, 139.54379649999998, 139.4962084, 139.47725300000002, 139.40952679999998, 139.40136670000004, 139.31035739999993, 139.705734, 139.66126680000002, 139.63070389999996, 139.53857500000004, 139.4329335, 139.48232830000006, 139.8994156, 140.04961500000002, 140.00057889999994, 139.62628459999996, 139.7956385, 140.86612300000002, 141.34382140000002};
    //店舗データの設定
    int i, j;
    for (i = 0; i < SIZE; i++) {
        shop[i].set_x(cordinates_x[i]);
        shop[i].set_y(cordinates_y[i]);
        shop[i].set_name(names[i]);
    }
    //巡回ルートのデータを持つ遺伝子の宣言
    int genes[NUM_OF_GENES][SIZE];
    //乱数の種を初期化
    srand((unsigned)time(NULL));
    //geneに巡回ルートを組み込む
    for (i = 0; i < NUM_OF_GENES; i++) {
        makeRoute(genes[i]);
    }
    //遺伝子の交配を繰り返す
    for (i = 0; i < 10000; i++) {
        getNextGeneration(genes);
    }
    //それぞれのルートの合計距離のソート
    float distance[NUM_OF_GENES]; //巡回ルートの合計距離を記録
    int rank[NUM_OF_GENES]; //ソート結果を記録
    for (i = 0; i < NUM_OF_GENES; i++) {
        rank[i] = i;
    }
    for (i = 0; i < NUM_OF_GENES; i++) {
        distance[i] = getTotalDistance(genes[i]);
    }
    int tmp;
    for (i = 0; i < NUM_OF_GENES; i++) {
        for (j = i + 1; j < NUM_OF_GENES - 1; j++) {
            if (distance[i] < distance[j]) {
                tmp = rank[i];
                rank[i] = rank[j];
                rank[j] = tmp;
            }
        }
    }
    printf("結果は以下のようになりました\n");
    for (i = 0; i < SIZE; i++) {
        printf("%d.%s\n", i + 1, shop[genes[rank[0]][i]].get_name());
    }
    printf("(合計距離:%f)\n", distance[rank[0]]);
    
    return 0;
}

//ランダムに巡回ルートを作成する関数の定義
void makeRoute(int *gene) {
    //配列の初期化
    int i;
    for (i = 0; i < SIZE; i++){
        gene[i] = i;
    }
    //シャッフルする
    int tmp;
    int num;
    for (i = 0; i < 200; i++) {
        num = rand() % SIZE;
        tmp = gene[num];
        if (num == SIZE - 1) {
            gene[num] = gene[0];
            gene[0] = tmp;
        } else {
            gene[num] = gene[num + 1];
            gene[num + 1] = tmp;
        }
    }
}
//２店舗間の距離を返す関数の定義
float getDistance(shops shop1, shops shop2) {
    return sqrt(pow(shop1.get_x() - shop2.get_x(), 2) + pow(shop1.get_y() - shop2.get_y(), 2));
}

//巡回ルートの合計距離を返す関数の定義
float getTotalDistance(int* gene) {
    float result;
    result = 0;
    int i;
    for (i = 0; i < SIZE - 2; i++) {
        result += getDistance(shop[gene[i]], shop[gene[i+1]]);
    }
    return result;
}

//遺伝子同士を交配する関数
void getNextGeneration(int (*genes)[SIZE]) {
    int i, j;
    //それぞれのルートの合計距離のソート
    float distance[12]; //巡回ルートの合計距離を記録
    int rank[12]; //ソート結果を記録
    for (i = 0; i < NUM_OF_GENES; i++) {
        rank[i] = i;
    }
    for (i = 0; i < NUM_OF_GENES; i++) {
        distance[i] = getTotalDistance(genes[i]);
    }
    int tmp;
    for (i = 0; i < NUM_OF_GENES; i++) {
        for (j = i + 1; j < NUM_OF_GENES - 1; j++) {
            if (distance[i] < distance[j]) {
                tmp = rank[i];
                rank[i] = rank[j];
                rank[j] = tmp;
            }
        }
    }
    
    //親を決める
    int winners[21];
    for (i = 0; i < 21; i++) {
        if (i < 6) {
            winners[i] = rank[0];
        } else if (i < 11) {
            winners[i] = rank[1];
        } else if (i < 15) {
            winners[i] = rank[2];
        } else if (i < 18) {
            winners[i] = rank[3];
        } else if (i < 20) {
            winners[i] = rank[4];
        } else {
            winners[i] = rank[5];
        }
    }
    int a, b;
    int flag;
    int parents[3][2];
    for (i = 0; i < 3; i++) {
        flag = 1;
        while (flag) {
            a = rand() % 21;
            b = rand() % 21;
            if (winners[a] == winners[b]) {
                continue;
            } else {
                parents[i][0] = winners[a];
                parents[i][1] = winners[b];
                flag = !flag;
            }
        }
    }
    /*親を交配させる*/
    int cross_points[2] = {12, 27};
    int cross_relation[15][2];
    int notCrossedPoint[SIZE];
    int flag2;
    int k;
    for (i = 0; i < 3; i++) {
        //交叉点を決め、交叉させる
        for (j = cross_points[0]; j < cross_points[1]; j++) {
            genes[rank[NUM_OF_GENES - (i * 2 + 1)]][j] = genes[parents[i][0]][j];
            genes[rank[NUM_OF_GENES - (i * 2 + 2)]][j] = genes[parents[i][1]][j];
        }
        //交叉した点の関係を記録する
        for (j = 0; j < cross_points[1] - cross_points[0]; j++) {
            cross_relation[j][0] = genes[parents[i][0]][cross_points[0] + j];
            cross_relation[j][1] = genes[parents[i][1]][cross_points[0] + j];
        }
        //交叉していない点を記録する
        for (j = 0; j < SIZE; j++) {
            flag = 0;
            for (k = cross_points[0]; k < cross_points[1]; k++) {
                if (j == genes[parents[i][0]][k] || j == genes[parents[i][1]][k]) {
                    flag = 1;
                } else {
                    continue;
                }
            }
            if (flag) {
                notCrossedPoint[j] = j;
            } else {
                notCrossedPoint[j] = 40;
            }
        }
        //子供の残りの遺伝子を埋めていく
        for (j = 0; j < SIZE; j++) {
            if (j >= cross_points[0] && j < cross_points[1]) {
                continue;
            }
            flag = 0;
            flag2 = 0;
            for (k = 0; k < SIZE; k++) {
                if (genes[parents[i][0]][j] == notCrossedPoint[k]) {
                    flag = 1;
                }
                if (genes[parents[i][1]][j] == notCrossedPoint[k]) {
                    flag2 = 1;
                }
            }
            if (flag) {
                //交叉していない遺伝子だったらそのまま親から引き継ぐ
                genes[rank[NUM_OF_GENES - (i * 2 + 1)]][j] = genes[parents[i][0]][j];
            } else {
                //交叉している遺伝子だったら、交叉関係に基づき修正する
                for (k = 0; k < cross_points[1] - cross_points[0] + 1; k++) {
                    if (genes[parents[i][0]][j] == cross_relation[j][0]) {
                        genes[rank[NUM_OF_GENES - (i * 2 + 1)]][j] = cross_relation[k][1];
                    }
                    if (genes[parents[i][0]][j] == cross_relation[k][1]) {
                        genes[rank[NUM_OF_GENES - (i * 2 + 1)]][j] = cross_relation[k][0];
                    }
                }
            }
            if (flag2) {
                //交叉していない遺伝子だったらそのまま親から引き継ぐ
                genes[rank[NUM_OF_GENES - (i * 2 + 2)]][j] = genes[parents[i][1]][j];
            } else {
                //交叉している遺伝子だったら、交叉関係に基づき修正する
                for (k = 0; k < cross_points[1] - cross_points[0] + 1; k++) {
                    if (genes[parents[i][1]][j] == cross_relation[k][0]) {
                        genes[rank[NUM_OF_GENES - (i * 2 + 2)]][j] = cross_relation[k][1];
                    }
                    if (genes[parents[i][1]][j] == cross_relation[k][1]) {
                        genes[rank[NUM_OF_GENES - (i * 2 + 2)]][j] = cross_relation[k][0];
                    }
                }
            }
        }
    }
    //子供のいずれかに突然変異を起こさせる
    int n;
    flag = 1;
    //どの子供を突然変異させるか決める
    n = rand() % NUM_OF_GENES/2 + (NUM_OF_GENES/2);
    while (flag) {
        //どこの遺伝子を変異させるか決める
        a = rand() % SIZE;
        b = rand() % SIZE;
        //入れ替える
        if (a == b) {
            continue;
        } else {
            tmp = genes[rank[n]][a];
            genes[rank[n]][a] = genes[rank[n]][b];
            genes[rank[n]][b] = tmp;
            flag = !flag;
        }
    }
}