/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:32:29 by aallou-v          #+#    #+#             */
/*   Updated: 2024/06/13 17:38:35 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

using namespace std;

class Player {

protected:
	string	gpu;
	int		gold;
	int		silver;
	int		bronze;
	int		score;
	bool	ennemy;
public:
	// Constructeur
	Player(string _gpu, int _score, int _gold, int _silver, int _bronze, bool _ennemy)
		: gpu(_gpu), score(_score), gold(_gold), silver(_silver), bronze(_bronze), ennemy(_ennemy) {}
	Player()
		: gpu(""), score(-2), gold(-2), silver(-2), bronze(-2), ennemy(-2) {}

	virtual void	displayInfo() const = 0;
	virtual			~Player() {}

	// Getters
	string getGpu()	const { return gpu; }
	int getGold()	const { return gold; }
	int getSilver()	const { return silver; }
	int getBronze()	const { return bronze; }
	int getScore()	const { return score; }

	// Setters
	void setGpu(const string& _gpu) { gpu = _gpu; }
	void setGold(int _gold) { gold = _gold; }
	void setSilver(int _silver) { silver = _silver; }
	void setBronze(int _bronze) { bronze = _bronze; }
	void setScore(int _score) { score = _score; }

	void display() const {
		cerr << "---- PLAYER ----" << endl;
		cerr << "GPU: " << gpu << endl;
		cerr << "Médailles d'or: " << gold << endl;
		cerr << "Médailles d'argent: " << silver << "" << endl;
		cerr << "Médailles de bronze: " << bronze << "" << endl;
		cerr << "Score: " << score << "" << endl;
	}
};

class Coureur : public Player {
private:
	int	position;
	int	etourdit;

public:

	Coureur(string _gpu, int _score, int _gold, int _silver, int _bronze, bool _ennemy, int _pos, int _etou)
		: Player(_gpu, _score, _gold, _silver, _bronze, _ennemy), position(_pos), etourdit(_etou) {}
	Coureur()
		: Player(), position(-2), etourdit(-2) {}

	void displayInfo() const override {
		cerr << "---- COUREUR ----" << endl;
		cerr << "GPU: " << gpu << endl;
		cerr << "Médailles d'or: " << gold << endl;
		cerr << "Médailles d'argent: " << silver << endl;
		cerr << "Médailles de bronze: " << bronze << endl;
		cerr << "Position: " << position << endl;
		cerr << "Etourdit: " << etourdit << endl;
	}

	// Getters
	int	getPosition() const { return position; }
	int	getEtourdit() const { return etourdit; }

	// Setters
	void	setPosition(int pos) { position = pos; }
	void	setEtourdit(int etou) { etourdit = etou; }

	bool can_foward(int step) const {
		if (getEtourdit() > 0)
			return false;
		for(int i = 1; i <= step; i++)
		{
			if (gpu.length() < getPosition() + i)
				return true;
			if (gpu.at(getPosition() + i) == '#')
				return false;
		}
		return true;
	}

	bool areOnlyDots()
	{
		for (int i = getPosition(); i < gpu.size(); ++i)
		{
			if (gpu[i] != '.' && gpu[i] != ' ')
				return false;
		}
		return true;
	}

	int	whereIam(Coureur *ennemi1, Coureur *ennemi2)
	{
		if (getPosition() - 2 > ennemi1->getPosition() && getPosition() - 2 > ennemi2->getPosition())
			return (1);
		else if (getPosition() > ennemi1->getPosition() && getPosition() < ennemi2->getPosition())
			return (2);
		else if (getPosition() < ennemi1->getPosition() && getPosition() > ennemi2->getPosition())
			return (2);
		else if (getPosition() < ennemi1->getPosition() && getPosition() < ennemi2->getPosition())
			return (3);
		else if (getPosition() == ennemi1->getPosition() && getPosition() == ennemi2->getPosition())
			return (2);
		else if (getPosition() == ennemi1->getPosition() && getPosition() < ennemi2->getPosition())
			return (2);
		else if (getPosition() < ennemi1->getPosition() && getPosition() == ennemi2->getPosition())
			return (2);
		return (2);
	}

	string	getBetterMove(Coureur *ennemi1, Coureur *ennemi2)
	{
		if (areOnlyDots())
		{
			if (!ennemi1->areOnlyDots() && !ennemi2->areOnlyDots())
				return ("SKIP");
			else
			{
				if (ennemi1->areOnlyDots() && !ennemi2->areOnlyDots())
				{
					if (getPosition() - 2 > ennemi1->getPosition())
						return ("SKIP");
					if (getPosition() + 4 < ennemi1->getPosition())
						return ("SKIP");
					return ("RIGHT");
				}
				else if (!ennemi1->areOnlyDots() && ennemi2->areOnlyDots())
				{
					if (getPosition() - 2 > ennemi2->getPosition())
						return ("SKIP");
					if (getPosition() + 4 < ennemi2->getPosition())
						return ("SKIP");
					return ("RIGHT");
				}
				else
				{
					if (getPosition() - 2 > ennemi1->getPosition() && getPosition() - 2 > ennemi2->getPosition())
						return ("SKIP");
					if (getPosition() + 4 < ennemi1->getPosition() && getPosition() + 4 < ennemi2->getPosition())
						return ("SKIP");
					return ("RIGHT");
				}
			}
			return ("SKIP");
		}
		if (whereIam(ennemi1, ennemi2) == 1)
			return ("SKIP");
		if (whereIam(ennemi1, ennemi2) == 2)
		{
			if (can_foward(3))
				return ("RIGHT");
			if (can_foward(2))
				return ("UP");
			if (can_foward(1))
				return ("LEFT");
		}
		if (whereIam(ennemi1, ennemi2) == 3)
		{
			if (can_foward(3))
				return ("RIGHT");
			if (can_foward(2))
				return ("UP");
			if (can_foward(1))
				return ("LEFT");
		}
	}
};

class Archer : public Player {
private:
	int	x;
	int	y;

public:
	// Constructeur
	Archer(string _gpu, int _score, int _gold, int _silver, int _bronze, bool _ennemy, int _x, int _y)
		: Player(gpu, _score, _gold, _silver, _bronze, _ennemy), x(_x), y(_y) {}
	Archer()
		: Player(), x(-2), y(-2) {}

	// Redéfinition de la méthode virtuelle
	void displayInfo() const override {
		cerr << "---- Archer ----" << endl;
		cerr << "GPU: " << gpu << endl;
		cerr << "Médailles d'or: " << gold << endl;
		cerr << "Médailles d'argent: " << silver << endl;
		cerr << "Médailles de bronze: " << bronze << endl;
		cerr << "Coordonne X: " << x << endl;
		cerr << "Coordonne Y: " << y << endl;
	}

	// Getters
	int getX() const { return x; }
	int getY() const { return y; }

	// Setters
	void setX(int x_) { x = x_; }
	void setY(int y_) { y = y_; }
};

class Roller : public Player {
private:
	int	stepDo;
	int	risk;
	int	round;

public:
	// Constructeur
	Roller(string _gpu, int _score, int _gold, int _silver, int _bronze, bool _ennemy, int step, int rsk, int rnd)
		: Player(_gpu, score, _gold, _silver, _bronze, _ennemy), stepDo(step), risk(rsk), round(rnd) {}
	Roller()
		: Player(), stepDo(-2), risk(-2), round(-2) {}

	// Redéfinition de la méthode virtuelle
	void displayInfo() const override {
		cerr << "---- Roller ----" << endl;
		cerr << "GPU: " << gpu << endl;
		cerr << "Médailles d'or: " << gold << endl;
		cerr << "Médailles d'argent: " << silver << endl;
		cerr << "Médailles de bronze: " << bronze << endl;
		cerr << "StepDo: " << stepDo << endl;
		cerr << "Risk: " << risk << endl;
		cerr << "Round: " << round << endl;
	}

	// Getters
	int getStepDo() const { return stepDo; }
	int getRisk() const { return risk; }
	int getRound() const { return round; }

	// Setters
	void setStepDo(int step) { stepDo = step; }
	void setRisk(int rsk) { risk = rsk; }
	void setRound(int rnd) { round = rnd; }
};

class Ella : public Player {
private:
	int	points;
	int	combo;

public:
	// Constructeur
	Ella(string _gpu, int _score, int _gold, int _silver, int _bronze, bool _ennemy, int _points, int _combo)
		: Player(_gpu, score, _gold, _silver, _bronze, _ennemy), points(_points), combo(_combo) {}
	Ella()
		: Player(), points(-2), combo(-2) {}

	// Redéfinition de la méthode virtuelle
	void displayInfo() const override {
		cerr << "---- Roller ----" << endl;
		cerr << "GPU: " << gpu << endl;
		cerr << "Médailles d'or: " << gold << endl;
		cerr << "Médailles d'argent: " << silver << endl;
		cerr << "Médailles de bronze: " << bronze << endl;
		cerr << "Points: " << points << endl;
		cerr << "Combo: " << combo << endl;
	}

	// Getters
	int getPoints() const { return points; }
	int getCombo() const { return combo; }

	// Setters
	void setPoints(int _points) { points = _points; }
	void setCombo(int _combo) { combo = _combo; }
};

int main()
{
	int		player_idx;
	int		nb_games;
	int		count = 1;
	int		reg_0;
	int		reg_1;
	int		reg_2;
	int		reg_3;
	int		reg_4;
	int		reg_5;
	int		reg_6;

	int		score;
	int		gold_run;
	int		silver_run;
	int		bronze_run;
	int		gold_bow;
	int		silver_bow;
	int		bronze_bow;
	int		gold_roller;
	int		silver_roller;
	int		bronze_roller;
	int		gold_ella;
	int		silver_ella;
	int		bronze_ella;
	string	score_info;
	string	gpu;

	cin >> player_idx; cin.ignore();
	cin >> nb_games; cin.ignore();

	Coureur	*coureur[3];
	Roller	*roller[3];
	Ella	*ella[3];
	Archer	*archer[3];
	for (size_t i = 0; i < 3; i++)
		coureur[i] = new Coureur();
	for (size_t i = 0; i < 3; i++)
		roller[i] = new Roller();
	for (size_t i = 0; i < 3; i++)
		ella[i] = new Ella();
	for (size_t i = 0; i < 3; i++)
		archer[i] = new Archer();
	while (1) {
		//PARSING DATA
		for (int i = 0; i < 3; i++) {
			//getline(cin, score_info);
			/*
			SCORE : 0
			HAIE GOLD 1 : 0
			HAIE SILVER 1 : 0
			HAIE BRONZE 1 : 0
			ARCHER GOLD 2 : 0
			ARCHER SILVER 2 : 0
			ARCHER BRONZE 2 : 0
			ROLLER SCORE : 0
			ROLLER SCORE : 0
			ROLLER SCORE : 0
			ELLA SCORE : 0
			ELLA SCORE : 0
			ELLA SCORE : 0
			*/
			cin >> score >>
			gold_run >>
			silver_run >>
			bronze_run >>
			gold_bow >>
			silver_bow >>
			bronze_bow >>
			gold_roller >>
			silver_roller >>
			bronze_roller >>
			gold_ella >>
			silver_ella >>
			bronze_ella;
			cin.ignore();
			if (player_idx == i)
			{
				coureur[0]->setScore(score);
				coureur[0]->setGold(gold_run);
				coureur[0]->setSilver(silver_run);
				coureur[0]->setBronze(bronze_run);
				archer[0]->setScore(score);
				archer[0]->setGold(gold_bow);
				archer[0]->setSilver(silver_bow);
				archer[0]->setBronze(bronze_bow);
				roller[0]->setScore(score);
				roller[0]->setGold(gold_roller);
				roller[0]->setSilver(silver_roller);
				roller[0]->setBronze(bronze_roller);
				ella[0]->setScore(score);
				ella[0]->setGold(gold_ella);
				ella[0]->setSilver(silver_ella);
				ella[0]->setBronze(bronze_ella);
				continue ;
			}
			if (count > 2)
				continue ;
			coureur[count]->setScore(score);
			coureur[count]->setGold(gold_run);
			coureur[count]->setSilver(silver_run);
			coureur[count]->setBronze(bronze_run);
			archer[count]->setScore(score);
			archer[count]->setGold(gold_bow);
			archer[count]->setSilver(silver_bow);
			archer[count]->setBronze(bronze_bow);
			roller[count]->setScore(score);
			roller[count]->setGold(gold_roller);
			roller[count]->setSilver(silver_roller);
			roller[count]->setBronze(bronze_roller);
			ella[count]->setScore(score);
			ella[count]->setGold(gold_ella);
			ella[count]->setSilver(silver_ella);
			ella[count]->setBronze(bronze_ella);
			count++;
		}


		for (int i = 0; i < nb_games; i++) {
			cin >> gpu >> reg_0 >> reg_1 >> reg_2 >> reg_3 >> reg_4 >> reg_5 >> reg_6; cin.ignore();
			if (i == 0) // SAUT DE HAIE
			{
				coureur[0]->setGpu(gpu);
				coureur[1]->setGpu(gpu);
				coureur[2]->setGpu(gpu);
				if (player_idx == 0)
				{
					coureur[0]->setPosition(reg_0);
					coureur[1]->setPosition(reg_1);
					coureur[2]->setPosition(reg_2);
					coureur[0]->setEtourdit(reg_3);
					coureur[1]->setEtourdit(reg_4);
					coureur[2]->setEtourdit(reg_5);
				}
				if (player_idx == 1)
				{
					coureur[0]->setPosition(reg_1);
					coureur[1]->setPosition(reg_0);
					coureur[2]->setPosition(reg_2);
					coureur[0]->setPosition(reg_4);
					coureur[1]->setPosition(reg_3);
					coureur[2]->setPosition(reg_5);
				}
				if (player_idx == 2)
				{
					coureur[0]->setPosition(reg_2);
					coureur[1]->setPosition(reg_0);
					coureur[2]->setPosition(reg_1);
					coureur[0]->setPosition(reg_5);
					coureur[1]->setPosition(reg_3);
					coureur[2]->setPosition(reg_4);
				}
			}
			if (i == 1) //ARCHER
			{
				archer[0]->setGpu(gpu);
				archer[1]->setGpu(gpu);
				archer[2]->setGpu(gpu);
				if (player_idx == 0)
				{
					archer[0]->setX(reg_0);
					archer[1]->setX(reg_1);
					archer[2]->setX(reg_2);
					archer[0]->setY(reg_3);
					archer[1]->setY(reg_4);
					archer[2]->setY(reg_5);
				}
				if (player_idx == 1)
				{
					archer[0]->setX(reg_1);
					archer[1]->setX(reg_0);
					archer[2]->setX(reg_2);
					archer[0]->setY(reg_4);
					archer[1]->setY(reg_3);
					archer[2]->setY(reg_5);
				}
				if (player_idx == 2)
				{
					archer[0]->setX(reg_2);
					archer[1]->setX(reg_0);
					archer[2]->setX(reg_1);
					archer[0]->setY(reg_5);
					archer[1]->setY(reg_3);
					archer[2]->setY(reg_4);
				}
			}
			if (i == 2) //ROLLER
			{
				roller[0]->setGpu(gpu);
				roller[1]->setGpu(gpu);
				roller[2]->setGpu(gpu);
				roller[0]->setRound(reg_6);
				roller[1]->setRound(reg_6);
				roller[2]->setRound(reg_6);
				if (player_idx == 0)
				{
					roller[0]->setStepDo(reg_0);
					roller[1]->setStepDo(reg_1);
					roller[2]->setStepDo(reg_2);
					roller[0]->setRisk(reg_3);
					roller[1]->setRisk(reg_4);
					roller[2]->setRisk(reg_5);
				}
				if (player_idx == 1)
				{
					roller[0]->setStepDo(reg_1);
					roller[1]->setStepDo(reg_0);
					roller[2]->setStepDo(reg_2);
					roller[0]->setRisk(reg_4);
					roller[1]->setRisk(reg_3);
					roller[2]->setRisk(reg_5);
				}
				if (player_idx == 2)
				{
					roller[0]->setStepDo(reg_2);
					roller[1]->setStepDo(reg_0);
					roller[2]->setStepDo(reg_1);
					roller[0]->setRisk(reg_5);
					roller[1]->setRisk(reg_3);
					roller[2]->setRisk(reg_4);
				}
			}
			if (i == 3) //ARCHER
			{
				ella[0]->setGpu(gpu);
				ella[1]->setGpu(gpu);
				ella[2]->setGpu(gpu);
				if (player_idx == 0)
				{
					ella[0]->setPoints(reg_0);
					ella[1]->setPoints(reg_1);
					ella[2]->setPoints(reg_2);
					ella[0]->setCombo(reg_3);
					ella[1]->setCombo(reg_4);
					ella[2]->setCombo(reg_5);
				}
				if (player_idx == 1)
				{
					ella[0]->setPoints(reg_1);
					ella[1]->setPoints(reg_0);
					ella[2]->setPoints(reg_2);
					ella[0]->setCombo(reg_4);
					ella[1]->setCombo(reg_3);
					ella[2]->setCombo(reg_5);
				}
				if (player_idx == 2)
				{
					ella[0]->setPoints(reg_2);
					ella[1]->setPoints(reg_0);
					ella[2]->setPoints(reg_1);
					ella[0]->setCombo(reg_5);
					ella[1]->setCombo(reg_3);
					ella[2]->setCombo(reg_4);
				}
			}
		}

		//IN GAME
		cout << "LEFT" << endl;
	}
}