#include "setup.txt"

bool fury;
int level = 1;

void myExit(int inf);

struct Pictures
{
	vector < string > pictureBasick;
	vector < string > pictureAttack;
	vector < string > pictureDefense;
};

class pers
{
    public:
        string nickName;
        int health = 1000;
        int armor = 0;
        int luck = 1;
        int attack = 100;
        int typeArmor = 0;
        int talant = 0;
        int mana = 0;

    public: Pictures pictures;

    public: inline void makePicture(vector < string > Basick, vector < string > Attack, vector < string > Defense, int type)
    {
        pictures.pictureAttack = Attack;
        pictures.pictureBasick = Basick;
        pictures.pictureDefense = Defense;

        armor -= typeArmor*5;
        typeArmor = type;
        armor += typeArmor*5;

        if(armor > 50)
        {
            talant += armor - 50;
            armor = 50;
        }

        return;
    }

    public: inline void writePicture(int typePicture)
    {
        if (typePicture == 1)
        {
            for (int i = 0; i < pictures.pictureAttack.sz; i++)
            {
                cout << pictures.pictureAttack[i] << "\n";
            }
        }
        else
        if (typePicture == 2)
        {
            for (int i = 0; i < pictures.pictureBasick.sz; i++)
            {
                cout << pictures.pictureBasick[i] << "\n";
            }
        }
        else
        {
            for (int i = 0; i < pictures.pictureDefense.sz; i++)
            {
                cout << pictures.pictureDefense[i] << "\n";
            }
        }

        return;
    }

    public: inline void writeStats(bool fury = 0)
    {
        cout << "------------------------|\n";
        cout << "\n\t" << nickName << "\n\n";
        if (fury) cout << "\t(fury)\n";

        cout << "health (armor): " << health << " (" << armor << ")\n";
        cout << "attack (luck):  " << attack << " (" << luck << ")\n";
        cout << "mana: ";

        for (int i = 1; i <= mana; i++)
        {
            cout << '*';

            if (i % 5 == 0) cout << ' ';
        }

        cout << "\n\n";

        return;
    }

    public: inline int calcAttack()
    {
        srand(time(0));

        int valAttack;
        int maxPersent = 0;

        for (int i = 1; i <= luck; i++)
        {
            maxPersent = max(maxPersent, (rand() % 101));
        }

        valAttack = (attack*maxPersent) / 100;

        return valAttack;
    }

    public: void calcDamage(int valAttack)
    {
        valAttack = ((100 - armor)*valAttack) / 100;

        health = health - min(health, max(0, valAttack));

        return;
    }

    public: void generateMob(int level)
    {
        health += 10 * (level - 1);
        armor += level / 20 * 3;
        attack += (level / 5) * 10;
        luck += level / 20;

        if (level % 20 == 0)
        {
            health *= 1.25;
            armor *= 1.25;
            attack *= 1.25;
            luck *= 1.25;

            makePicture(LegendarySkeletonBase, LegendarySkeletonAttack, LegendarySkeletonDefense, 0);
        }
        else
        if (level % 5 == 0)
        {
            health *= 1.15;
            armor *= 1.15;
            attack *= 1.15;
            luck *= 1.15;

            makePicture(RareSkeletonBase, RareSkeletonAttack, RareSkeletonDefense, 0);
        }
        else
        {
            makePicture(SkeletonBase, SkeletonAttack, SkeletonDefense, 0);
        }

        if(armor > 50)
        {
            health += 100*(armor - 50);
            armor = 50;
        }

        return;
    }

    public: void defense()
    {
        luck++;
        return;
    }

};

pers player, mob;

class Inventory
{
    public: int cntHeal = 0;
    public: int cntArmor = 0;
    public: int cntLuck = 0;
    public: int cntAttack = 0;

    public: int cntBigHeal = 0;
    public: int cntBigArmor = 0;
    public: int cntBigLuck = 0;
    public: int cntBigAttack = 0;

    public: bool heavyArmor = 0;
    public: bool middleArmor = 0;
    public: bool lightArmor = 0;

    inline void writeInventory()
    {
        cout << "Inventory\n\n";
        cout << "Name:          Count: \n";
        cout << " heal   (+10%) - " << cntHeal << "\n";
        cout << " armor    (+2) - " << cntArmor << "\n";
        cout << " attack (+10%) - " << cntAttack << "\n";
        cout << " luck     (+2) - " << cntLuck << "\n\n";
    }

    inline void potion(pers & playerBasic, pers & playerCurent)
    {
        char input;

        wait(0);

        while (1)
        {
            playerCurent.writePicture(2);
            playerCurent.writeStats(fury);

            cout << "Inventory\n\n";

            cout << "Name:          Count: \n";
            cout << " heal   (+10%) - " << cntHeal << "\n";
            cout << " armor    (+2) - " << cntArmor << "\n";
            cout << " attack (+10%) - " << cntAttack << "\n";
            cout << " luck     (+2) - " << cntLuck << "\n\n";

            cout << "Press to continue:\n";
            cout << "\t1 - heal\n";
            cout << "\t2 - armor\n";
            cout << "\t3 - attack\n";
            cout << "\t4 - luck\n";
            cout << "\tb - back to the battle\n";

            input = getch();

            switch (input)
            {
                case '1':
				{
                    if (cntHeal < 1)
                    {
                        writeError();
                    }
                    else
                    {
                        playerCurent.health += playerBasic.health * 0.10;

                        if (fury)
                        {
                            fury = 0;
                            playerCurent.attack /= 1.5;
                            playerCurent.armor /= 1.5;
                            playerCurent.luck--;
                        }

                        cntHeal--;
                        wait(0);
                    }
				}; break;
				case '2':
				{
                    if (cntArmor < 1)
                    {
                        writeError();
                    }
                    else
                    {
                        playerCurent.armor += 2;
                        cntArmor--;
                        wait(0);
                    }
				}; break;
				case '3':
				{
                    if (cntAttack < 1)
                    {
                        writeError();
                    }
                    else
                    {
                        playerCurent.attack += playerBasic.attack * 0.10;
                        cntAttack--;
                        wait(0);
                    }
				}; break;
				case '4':
				{
                    if (cntLuck < 1)
                    {
                        writeError();
                    }
                    else
                    {
                        playerCurent.luck += 2;
                        cntLuck--;
                        wait(0);
                    }
				}; break;
				case 'b': return; break;
				default: writeError(); break;
            }
        }
    }

    inline void chooseChest()
    {
        wait(0);

        char input;
        srand(time(0));

        while (1)
        {
            for (int i = 0; i < chest.sz; i++)
            {
                cout << chest[i] << "\n";
            }

            input = getch();

            if (input == 'l' || input == 'r' || input == 'm')
            {
                int val;

                if(!heavyArmor)
                {
                    val = rand() % 9;
                }else
                {
                    val = rand() % 4;
                }

                if(val == 8)
                {
                    if(!lightArmor)
                    {
                        wait();

                        player.makePicture(LightArmorBase, LightArmorAttack, LightArmorDefense, 1);
                        lightArmor = 1;

                        cout << "You got now Light Armor!\n";
                        wait(1500);

                        return;
                    }else
                    if(!middleArmor)
                    {
                        wait();

                        player.makePicture(MiddleArmorBase, MiddleArmorAttack, MiddleArmorDefense, 2);
                        middleArmor = 1;

                        cout << "You got now Middle Armor!\n";
                        wait(1500);

                        return;
                    }else
                    if(!heavyArmor)
                    {
                        wait();

                        player.makePicture(HeavyArmorBase, HeavyArmorAttack, HeavyArmorDefense, 3);
                        heavyArmor = 1;

                        cout << "You got now Heavy Armor!\n";
                        wait(1500);

                        return;
                    }
                }else
                if (val%4 == 0)
                {
                    cntHeal++;

                    wait(0);
                    cout << "You got one more HEAL potion\n";
                    wait(2000);

                    return;
                }else
                if (val%4 == 1)
                {
                    cntArmor++;

                    wait(0);
                    cout << "You got one more ARMOR potion\n";
                    wait(2000);

                    return;
                }else
                if (val%4 == 2)
                {
                    cntAttack++;

                    wait(0);
                    cout << "You got one more ATTACK potion\n";
                    wait(2000);

                    return;
                }else
                if (val%4 == 3)
                {
                    cntLuck++;

                    wait(0);
                    cout << "You got one more LUCK potion\n";
                    wait(2000);

                    return;
                }
            }
            else
            {
                writeError();
            }
        }
    }
};

Inventory inventory;

inline int menu(int nexLevel)
{
	wait(0);

	while (1)
	{
		cout << "Next level: " << nexLevel;

		if (nexLevel % 20 == 0)
		{
			cout << " - LEGENDARY\n\n";
		}
		else
		if (nexLevel % 5 == 0)
		{
			cout << " - Rare\n\n";
		}
		else
		{
			cout << "\n\n";
		}

		cout << "Press to continue:\n";
		cout << "\tn - next battle\n";
		cout << "\tu - update stats (talant(s) - " << player.talant << ")\n";
		///cout << "\tc - change weapon\n";        ### change weapon
		cout << "\te - exit\n";

		char input = getch();

		switch (input)
		{
            case 'n': return 1; break;
            case 'u': return 2; break;
			///case 'c': return 3; break;        ### change weapon
            case 'e': myExit(0); break;
            default: writeError(); break;
		}
	}
}

inline int updateStats()
{
	char input;

	wait(0);

	while (1)
	{
		player.writePicture(2);
		player.writeStats();

		cout << "\nYou have " << player.talant << " talant(s)\n\n";
		cout << "Press to update:\n";
		cout << "\t1 - +100 health (cost 1 talant)\n";
		cout << "\t2 -   +3  armor (cost 3 talant) (max count of armor - 50)\n";
		cout << "\t3 -  +10 attack (cost 1 talant)\n";
		cout << "\t4 -   +1   luck (cost 3 talant)\n\n";

		cout << "Press to continue:\n";
		cout << "\tn - next battle\n";
		cout << "\tm - menu\n";
		///cout << "\tc - change weapon\n";        ### change weapon
		cout << "\te - exit\n";

		input = getch();

		switch (input)
		{
            case '1':
            {
                if (player.talant < 1)
                {
                    writeError();
                }
                else
                {
                    player.talant--;
                    player.health += 100;
                    wait(0);
                }
            }; break;
            case '2':
            {
                if (player.talant < 3 || player.armor == 50)
                {
                    writeError();
                }
                else
                {
                    player.talant -= 3;
                    player.armor += 3;

                    if(player.armor > 50)
                    {
                        player.talant += player.armor - 50;
                        player.armor = 50;
                    }

                    wait(0);
                }
            }; break;
            case '3':
            {
                if (player.talant < 1)
                {
                    writeError();
                }
                else
                {
                    player.talant--;
                    player.attack += 10;
                    wait(0);
                }
            }; break;
            case '4':
            {
                if (player.talant < 3)
                {
                    writeError();
                }
                else
                {
                    player.talant -= 3;
                    player.luck++;
                    wait(0);
                }
            }; break;
            case 'n': return 1; break;
            case 'm': return 0; break;
			///case 'c': return 2; break;        ### change weapon
            case 'e': myExit(0); break;
            default: writeError(); break;
		}
	}
}

inline void writeFinalBattleWords(bool win)
{
	wait(0);

	if (win)
	{
		cout << "\tYOU WIN!!!\n\n";
	}
	else
	{
		cout << "\tYou lose...\n\n";
	}

	cout << "Let`s go to the next battle!\n";
	cout << "(Press any key to continue)\n";

	getch();

	return;
}

inline void move(pers player, int pos1, pers mob, int pos2, int level)
{
	wait(150);

	cout << "Level: " << level << "\n\n";
	player.writePicture(pos1);
	player.writeStats(fury);
	mob.writePicture(pos2);
	mob.writeStats();

	return;
}

inline bool fight(int level)
{
	char input;

	fury = 0;

	wait(0);

	pers playerLocal = player;
	pers mobLocal = mob;

	mobLocal.generateMob(level);

	while (1)
	{
		cout << "Level: " << level << "\n\n";
		playerLocal.writePicture(2);
		playerLocal.writeStats(fury);
		mobLocal.writePicture(2);
		mobLocal.writeStats();

		cout << "Press to continue:\n";
		cout << "\ta - attack\n";
		cout << "\td - defense\n";
		cout << "\tq - Holly Sword (make 75 damage, cost 10 mana)\n";
		cout << "\te - Gods` Pleasure (add 3 luck, cost 10 mana)\n";
		cout << "\ti - inventory\n";

		input = getch();

		switch (input)
		{
            case 'a':
            {
                move(playerLocal, 2, mobLocal, 2, level);
                move(playerLocal, 1, mobLocal, 2, level);
                mobLocal.calcDamage(playerLocal.calcAttack());
                move(playerLocal, 2, mobLocal, 2, level);

                if (mobLocal.health == 0) return 1;

                playerLocal.mana++;
            }; break;
            case 'd':
            {
                move(playerLocal, 2, mobLocal, 2, level);
                move(playerLocal, 3, mobLocal, 2, level);
                playerLocal.defense();
                move(playerLocal, 2, mobLocal, 2, level);

                playerLocal.mana += 2;
            }; break;
            case 'i':
            {
                inventory.potion(player, playerLocal);
                wait(0);
                continue;
            }; break;
            case 'q':
            {
                if (playerLocal.mana < 10)
                {
                    writeError();
                    continue;
                }
                else
                {
                    playerLocal.mana -= 10;
                    mobLocal.health -= min(mobLocal.health, 75);

                    wait(0);

                    if (mobLocal.health == 0) return 1;

                    continue;
                }
            }; break;
            case 'e':
            {
                if (playerLocal.mana < 10)
                {
                    writeError();
                    continue;
                }
                else
                {
                    playerLocal.mana -= 10;

                    playerLocal.luck += 3;

                    wait(0);

                    continue;
                }
            }; break;
            default:
            {
                writeError();
                continue;
            } break;
		}

		srand(time(0));

		input = rand() % 8;

		if (input == 0)
		{
			move(playerLocal, 2, mobLocal, 2, level);
			move(playerLocal, 2, mobLocal, 3, level);
			mobLocal.defense();
			move(playerLocal, 2, mobLocal, 2, level);
			wait(0);
		}
		else
		{
			move(playerLocal, 2, mobLocal, 2, level);
			move(playerLocal, 2, mobLocal, 1, level);
			playerLocal.calcDamage(mobLocal.calcAttack());
			move(playerLocal, 2, mobLocal, 2, level);
			wait(0);

			if (playerLocal.health == 0)
			{
				return 0;
			}
			if (playerLocal.health <= player.health * 0.1 && !fury)
			{
				fury = 1;
				playerLocal.attack *= 1.5;
				playerLocal.armor *= 1.5;
				playerLocal.luck++;
			}
		}
	}
}

inline void hello()
{
	cout << "\tConsole Dungeon\n\n";
	cout << "Creators:\n";
	cout << "\tIdea:\n";
	cout << "\t\tBugInSystem\n";
	cout << "\tCode:\n";
	cout << "\t\tBugInCode\n";
	cout << "\t\tReeWorld\n";
	cout << "\tTesting:\n";
	cout << "\t\tTheDarkness\n\n";
	cout << "Please, check that your console is full screen\n";
	cout << "Press any key to continue...\n";

	getch();

	return;
}

void cheat()
{
	string password;
	int typeOfArmor;

	wait(0);

	cout << "If you are developer or tester, please enter developers password\n(looking for password in code of game, function \'cheat\'):\n";
	cin >> password;
	cout << "\n";

	if (password == "Julick_ne_voruy")
	{
		cout << "You want to begin from level: ";
		cin >> level;
		cout << "\n";

		cout << "You want get type armor (0 - without, 1 - light, 2 - middle, 3 - heavy): ";
		cin >> typeOfArmor;
		cout << "\n";

		switch(typeOfArmor)
		{
            case 0:
            {
                player.makePicture(WithoutArmorBase, WithoutArmorAttack, WithoutArmorDefense, typeOfArmor);
            };break;
            case 1:
            {
                player.makePicture(LightArmorBase, LightArmorAttack, LightArmorDefense, typeOfArmor);
                inventory.lightArmor = 1;
            };break;
            case 2:
            {
                player.makePicture(MiddleArmorBase, MiddleArmorAttack, MiddleArmorDefense, typeOfArmor);
                inventory.lightArmor = 1;
                inventory.middleArmor = 1;
            }; break;
            case 3:
            {
                player.makePicture(HeavyArmorBase, HeavyArmorAttack, HeavyArmorDefense, typeOfArmor);
                inventory.lightArmor = 1;
                inventory.middleArmor = 1;
                inventory.heavyArmor = 1;
            }
		}

		cout << "You want to begin with count of talants: ";
		cin >> player.talant;
		cout << "\n";

		cout << "You want to begin each level with count of mana: ";
		cin >> player.mana;
		cout << "\n";

		cout << "You want to begin with count of Heal potion: ";
		cin >> inventory.cntHeal;
		cout << "\n";

		cout << "You want to begin with count of Armor potion: ";
		cin >> inventory.cntArmor;
		cout << "\n";

		cout << "You want to begin with count of Attack potion: ";
		cin >> inventory.cntAttack;
		cout << "\n";

		cout << "You want to begin with count of Luck potion: ";
		cin >> inventory.cntLuck;
		cout << "\n";

		cout << "Tank you, good testing, glhf))\n";
		cout << "Press any key to continue\n";
		getch();
	}
	else
	{
		cout << "Password is incorrect\n";
		cout << "Press any key to continue\n";
		getch();
	}

	return;
}

bool tryLoad(Inventory &inv, pers &per)
{
	string type;
	int stat, tlvl;
	ifstream cinf(per.nickName+".sf");

	if (cinf >> type >> stat)
	{
		if (type == "level"  && stat > 0)
		{
			tlvl = stat;
		}
		else { cinf.close(); return false; }
	}
	else { cinf.close(); return false; }

	if (cinf >> type >> stat)
	{
		if (type == "health"  && stat > 0)
		{
			per.health = stat;
		}
		else { cinf.close(); return false; }
	}
	else { cinf.close(); return false; }

	if (cinf >> type >> stat)
	{
		if (type == "armor"  && stat >= 0 && stat <= 50)
		{
			per.armor = stat;
		}
		else { cinf.close(); return false; }
	}
	else { cinf.close(); return false; }

	if (cinf >> type >> stat)
	{
		if (type == "luck"  && stat > 0)
		{
			per.luck = stat;
		}
		else { cinf.close(); return false; }
	}
	else { cinf.close(); return false; }

	if (cinf >> type >> stat)
	{
		if (type == "attack"  && stat > 0)
		{
			per.attack = stat;
		}
		else { cinf.close(); return false; }
	}
	else { cinf.close(); return false; }

	if (cinf >> type >> stat)
	{
		if (type == "typeArmor" && stat >= 0 && stat <= 3)
		{
			per.typeArmor = stat;
			if (stat == 0)
			{
				per.makePicture(WithoutArmorBase, WithoutArmorAttack, WithoutArmorDefense, stat);
			}
			else if (stat == 1)
			{
				inv.lightArmor = true;
				per.makePicture(LightArmorBase, LightArmorAttack, LightArmorDefense, stat);
			}
			else if (stat == 2)
			{
				inv.middleArmor = true;
				per.makePicture(MiddleArmorBase, MiddleArmorAttack, MiddleArmorDefense, stat);
			}
			else
			{
				inv.heavyArmor = true;
				per.makePicture(HeavyArmorBase, HeavyArmorAttack, HeavyArmorDefense, stat);
			}
		}
		else { cinf.close(); return false; }
	}
	else { cinf.close(); return false; }

	if (cinf >> type >> stat)
	{
		if (type == "talant" && stat >= 0)
		{
			per.talant = stat;
		}
		else { cinf.close(); return false; }
	}
	else { cinf.close(); return false; }

	if (cinf >> type >> stat)
	{
		if (type == "cntHeal" && stat >= 0)
		{
			inv.cntHeal = stat;
		}
		else { cinf.close(); return false; }
	}
	else { cinf.close(); return false; }

	if (cinf >> type >> stat)
	{
		if (type == "cntArmor" && stat >= 0)
		{
			inv.cntArmor = stat;
		}
		else { cinf.close(); return false; }
	}
	else { cinf.close(); return false; }

	if (cinf >> type >> stat)
	{
		if (type == "cntLuck" && stat >= 0)
		{
			inv.cntLuck = stat;
		}
		else { cinf.close(); return false; }
	}
	else { cinf.close(); return false; }

	if (cinf >> type >> stat)
	{
		if (type == "cntAttack" && stat >= 0)
		{
			inv.cntAttack = stat;
		}
		else { cinf.close(); return false; }
	}
	else { cinf.close(); return false; }

	level = tlvl;
	return true;
}

void askPreviousSave()
{
	wait();

	char input;
	string s;
	pers per;
	Inventory invent;

	cout << "Write your nickname and press enter:\n";
	while (1)
	{
		getline(cin, s);
		if (s != "")
		{
			break;
		}
	}
	for (auto &it : s)
	{
		if (it == ' ')
		{
			it = '_';
		}
	}
	per.nickName = s;

	if (tryLoad(invent, per))
	{
		cout << "Save loaded\nDo you want to continue previous game? If yes - press '1', else press '0'\n";
		while (1)
		{
			input = getch();
			if (input == '0')
			{
				level = 1;
				player.nickName = s;
				break;
			}
			else if (input == '1')
			{
				player = per;
				inventory = invent;
				player.nickName = s;
				break;
			}
		}
	}
	else
	{
		player.nickName = s;
		cout << "No save with this name\nPress any key to continue";
		getch();
	}

	wait();

}

void myExit(int inf=0)
{
	ofstream coutf(player.nickName + ".sf");

	coutf << "level " << level << "\n";
	coutf << "health " << player.health << "\n";
	coutf << "armor " << player.armor << "\n";
	coutf << "luck " << player.luck << "\n";
	coutf << "attack " << player.attack << "\n";
	coutf << "typeArmor " << player.typeArmor << "\n";
	coutf << "talant " << player.talant << "\n";
	coutf << "cntHeal " << inventory.cntHeal << "\n";
	coutf << "cntArmor " << inventory.cntArmor << "\n";
	coutf << "cntLuck " << inventory.cntLuck << "\n";
	coutf << "cntAttack " << inventory.cntAttack << "\n";

	coutf.close();

	exit(inf);
}

int main()
{
	player.makePicture(WithoutArmorBase, WithoutArmorAttack, WithoutArmorDefense, 0);

	hello();
	askPreviousSave();
	cheat();

	int function = 0;

	while (1)
	{
		switch (function)
		{
            case 0: function = menu(level); break;
            case 1:
            {
                bool x = fight(level);
                writeFinalBattleWords(x);

                if (x && level % 5 == 0)
                {
                    inventory.chooseChest();
                }

                level += x;

                if (x && level % 5 == 0) player.talant++; else
                if (x && level % 20 == 1) player.talant += 3; else
                if (x && level % 5 == 1) player.talant++;

                function = 0;
            }; break;
            case 2: function = updateStats(); break;
		}
	}
}
