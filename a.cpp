#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <utility>

#define rep(i, n) for(int i = 0; i < (n); i++)

// 工面算段, 工面算段II, 模範作業II, 模範作業III, 確信, ピース・バイ・ピース, ステディハンド, ステディハンドII, コンファートゾーン, マニピュレーション, マニピュレーションII, マスターズメンド, マスターズメンドII, 倹約, 倹約II

/*
コンファートゾーン: 毎ターンCPを8回復, 10ターン持続
マニピュレーション: 毎ターン耐久を10回復, 3ターン持続
マニピュレーションII: 毎ターン耐久を5回復, 8ターン持続
マスターズメンド: 耐久を30回復
マスターズメンドII: 耐久を60回復
 */

typedef std::string action;

int progress[3][2]; // 工面算段バフ, 作業アクションid
std::map<action, int> progress_actions = {
  {"模範作業II", 0},
  {"模範作業III", 1},
};
std::map<action, int> kumen_sandan = {
  {"工面算段", 1},
  {"工面算段II", 2}
};
std::map<action, int> cp_cost = {
  {"工面算段", 24},
  {"工面算段II", 32},
  {"模範作業II", 0},
  {"模範作業III", 7},
  {"確信", 6},
  {"ピース・バイ・ピース", 15},
  {"ステディハンド", 22},
  {"ステディハンドII", 25},
  {"コンファートゾーン", 66},
  {"マニピュレーション", 88},
  {"マニピュレーションII", 96},
  {"マスターズメンド", 92},
  {"マスターズメンドII", 160},
  {"倹約", 56},
  {"倹約II", 98}
};


int main() {
  int taikyu, kousu, saidai_hinshitsu;
  int cp;
  std::cin >> taikyu >> kousu >> saidai_hinshitsu;
  std::cin >> cp;
  rep(i, 3) {
    rep(j, 2) {
      std::cin >> progress[i][j];
    }
  }

  std::vector<std::string> actions(0);

  int steady_hand = 0;

  while (kousu > 0) {
    std::cerr << taikyu << " " << kousu << " " << cp << std::endl;
    if (taikyu <= 0) {
      // 耐久足りない
      std::cout << "IMPOSSIBLE" << std::endl;
      return 0;
    }
    std::vector<std::pair<int, action> > alts = {
      {progress[0][progress_actions["模範作業II"]], "模範作業II"},
      {progress[0][progress_actions["模範作業III"]], "模範作業III"},
      {kousu / 3, "ピース・バイ・ピース"}
    };

    // 3アクションを進む工数が大きい順に並べる
    std::sort(alts.begin(), alts.end(), [](std::pair<int, action> a1, std::pair<int, action> a2) -> bool {
	return a1.first > a2.first;
    });

    // CPが足りるアクションを選ぶ
    rep(i, 3) {
      if (alts[i].second == "ピース・バイ・ピース" && steady_hand <= 0) {
	if (cp >= cp_cost["ピース・バイ・ピース"] + cp_cost["ステディハンド"]) {
	  actions.push_back("ステディハンド");
	  actions.push_back("ピース・バイ・ピース");
	  steady_hand = 5;
	  kousu -= alts[i].first;
	  cp -= cp_cost["ピース・バイ・ピース"] + cp_cost["ステディハンド"];
	  break;
	}
      }
      else if (cp >= cp_cost[alts[i].second]) {
        actions.push_back(alts[i].second);
        kousu -= alts[i].first;
        cp -= cp_cost[alts[i].second];
        break;
      }
    }
    taikyu -= 10;
    steady_hand -= 1;
  }

  for (auto action : actions) {
    std::cout << action << std::endl;
  }

  return 0;
}
