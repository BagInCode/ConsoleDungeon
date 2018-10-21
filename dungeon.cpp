#include "setup.txt"

ll level = 1;

void myExit(ll inf);

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
        ll health = 10000;
        ll armor = 0;
        ll luck = 100;
        ll attack = 1000;
        ll typeArmor = 0;
        ll talant = 0;
        ll mana = 0;

    public: Pictures pictures;

    public: inline void makePicture(vector < string > Basick, vector < string > Attack, vector < string > Defense, ll type)
    {
        pictures.pictureAttack = Attack;
        pictures.pictureBasick = Basick;
        pictures.pictureDefense = Defense;

        armor -= typeArmor*5*deltArmor;
        typeArmor = type;
        armor += typeArmor*5*deltArmor;

        if(armor > 5000)
        {
            talant += armor - 50 * deltArmor;
            armor = 50 * deltArmor;
        }

        return;
    }

    public: inline void writePicture(ll typePicture)
    {
        if (typePicture == 1)
        {
            for (ll i = 0; i < pictures.pictureAttack.sz; i++)
            {
                cout << pictures.pictureAttack[i] << "\n";
            }
        }
        else
        if (typePicture == 2)
        {
            for (ll i = 0; i < pictures.pictureBasick.sz; i++)
            {
                cout << pictures.pictureBasick[i] << "\n";
            }
        }
        else
        {
            for (ll i = 0; i < pictures.pictureDefense.sz; i++)
            {
                cout << pictures.pictureDefense[i] << "\n";
            }
        }

        return;
    }

    public: inline void writeStats(bool fury = 0)
    {
        cout << "------------------------|\n";
        cout << "\t" << nickName << "\n";

        if (fury) cout << "\t(fury)\n";

        cout << "health (armor): " << health/10 << "." << health%10 << " (" << armor/deltArmor << ")\n";
        cout << "attack (luck):  " << attack/10 << "." << attack%10 << " (" << luck/deltLuck << ")\n";
        cout << "mana: ";

        for (ll i = 1; i <= mana; i++)
        {
            cout << char(248);

            if (i % 5 == 0) cout << ' ';
        }

        cout << "\n\n";

        return;
    }

    public: inline ll calcAttack()
    {
        srand(time(0));

        ll valAttack;
        ll maxPersent = 0;

        for (ll i = 1; i <= luck/deltLuck; i++)
        {
            maxPersent = max(maxPersent, (ll)(rand() % 101));
        }

        valAttack = (attack*maxPersent) / 100;

        return valAttack;
    }

    public: void calcDamage(ll valAttack)
    {
        valAttack = ((100 - armor/deltArmor)*valAttack) / 100;

        health = health - min(health, max(0ll, valAttack));

        return;
    }

    public: void generateMob(ll level)
    {
        health += deltHealth/10 * (level - 1);
        armor += level / 20 * 3 * deltArmor;
        attack += (level / 5) * deltAttack;
        luck += level / 20 * deltLuck;

        if (level % 20 == 0)
        {
            health = round(health * 1.25);
            armor = round(armor * 1.25);
            attack = round(attack * 1.25);
            luck = round(luck * 1.25);

            makePicture(LegendarySkeletonBase, LegendarySkeletonAttack, LegendarySkeletonDefense, 0);
        }
        else
        if (level % 5 == 0)
        {
            health = round(health * 1.15);
            armor = round(armor * 1.15);
            attack = round(attack * 1.15);
            luck = round(luck * 1.15);

            makePicture(RareSkeletonBase, RareSkeletonAttack, RareSkeletonDefense, 0);
        }
        else
        {
            makePicture(SkeletonBase, SkeletonAttack, SkeletonDefense, 0);
        }

        if(armor > 50*deltArmor)
        {
            health += deltHealth*(armor - 50*deltArmor);
            armor = 50 * deltArmor;
        }

        if(luck > 15 * deltLuck)
        {
            attack += (luck-15*deltLuck)*3*deltLuck;
            luck = 15*deltLuck;
        }

        return;
    }

    public: void defense()
    {
        luck += deltLuck;
        return;
    }

    public: void setNickName(string & nick)
    {
        nickName = nick;
        return;
    }

};

pers player, mob;

class Inventory
{
    public: ll cntSmallHeal = 0;
    public: ll cntSmallArmor = 0;
    public: ll cntSmallLuck = 0;
    public: ll cntSmallAttack = 0;

    public: ll cntBigHeal = 0;
    public: ll cntBigArmor = 0;
    public: ll cntBigLuck = 0;
    public: ll cntBigAttack = 0;

    public: bool heavyArmor = 0;
    public: bool middleArmor = 0;
    public: bool lightArmor = 0;

    public: inline void usingPotion(pers & playerBasic, pers & playerCurent, bool & fury)
    {
        char input;

        wait(0);

        while (1)
        {
            playerCurent.writePicture(2);
            playerCurent.writeStats(fury);

            cout << "Inventory\n\n";

            cout << "Name:                                        Count: \n";
            cout << " small heal       (+15% hp from basic, -5 armor) - " << cntSmallHeal << "\n";
            cout << " small armor      (+10 armor, -5% hp from basic) - " << cntSmallArmor << "\n";
            cout << " small attack (+15% attack from basic, -1 luck*) - " << cntSmallAttack << "\n";
            cout << " small luck     (+2 luck, -5% attack from basic) - " << cntSmallLuck << "\n\n";

            cout << " big heal        (+25% hp from basic, -10 armor) - " << cntBigHeal << "\n";
            cout << " big armor       (+20 armor, -10% hp from basic) - " << cntBigArmor << "\n";
            cout << " big attack  (+25% attack from basic, -2 luck**) - " << cntBigAttack << "\n";
            cout << " big luck      (+5 luck, -10% attack from basic) - " << cntBigLuck << "\n\n";

            cout << "* - you must have more then 1 luck\n";
            cout << "** - you must have more then 2 luck\n\n";

            cout << "Press to continue:\n";
            cout << "\t1 - small heal\n";
            cout << "\t2 - small armor\n";
            cout << "\t3 - small attack\n";
            cout << "\t4 - small luck\n\n";

            cout << "\t5 - big heal\n";
            cout << "\t6 - big armor\n";
            cout << "\t7 - big attack\n";
            cout << "\t8 - big luck\n\n";

            cout << "\tb - back to the battle\n";

            input = getch();

            switch (input)
            {
                case '1': /// Small heal (+15% hp, -5 armor)
				{
                    if (cntSmallHeal < 1)
                    {
                        writeError();
                    }
                    else
                    {
                        playerCurent.health += round(playerBasic.health * 0.15);

                        if (fury)
                        {
                            fury = 0;

                            playerCurent.attack = round(playerCurent.attack/1.5);
                            playerCurent.armor = round(playerCurent.armor/1.5);
                            playerCurent.luck -= deltLuck;
                        }

                        playerCurent.armor -= 5*deltArmor;

                        cntSmallHeal--;
                        wait(0);
                    }
				}; break;
				case '2': /// Small armor (+10 armor, -5% hp)
				{
                    if (cntSmallArmor < 1 || round(playerBasic.health * 0.05) >= playerCurent.health)
                    {
                        writeError();
                    }
                    else
                    {
                        playerCurent.armor += 10*deltArmor;
                        playerCurent.health -= round(playerBasic.health*0.05);

                        if(!fury && playerCurent.health <= round(playerBasic.health * 0.1))
                        {
                            fury = 1;

                            playerCurent.attack = round(playerCurent.attack * 1.5);
                            playerCurent.armor = round(playerCurent.attack * 1.5);
                            playerCurent.luck += deltLuck;
                        }

                        cntSmallArmor--;
                        wait(0);
                    }
				}; break;
				case '3': /// Small attack (+15% attack, -1 luck)
				{
                    if (cntSmallAttack < 1 || playerCurent.luck < 2*deltLuck)
                    {
                        writeError();
                    }
                    else
                    {
                        playerCurent.attack += round(playerBasic.attack * 0.15);
                        playerCurent.luck -= deltLuck;

                        cntSmallAttack--;

                        wait(0);
                    }
				}; break;
				case '4': /// Small luck (+2 luck, -5% attack)
				{
                    if (cntSmallLuck < 1)
                    {
                        writeError();
                    }
                    else
                    {
                        playerCurent.luck += 2*deltLuck;
                        playerCurent.attack -= round(playerBasic.attack * 0.05);

                        cntSmallLuck--;
                        wait(0);
                    }
				}; break;
                case '5': /// Big heal (+25% hp, -10 armor)
				{
                    if (cntBigHeal < 1)
                    {
                        writeError();
                    }
                    else
                    {
                        playerCurent.health += round(playerBasic.health * 0.25);

                        if (fury)
                        {
                            fury = 0;

                            playerCurent.attack = round(playerCurent.attack / 1.5);
                            playerCurent.armor = round(playerCurent.armor / 1.5);
                            playerCurent.luck -= deltLuck;
                        }

                        playerCurent.armor -= 10*deltArmor;

                        cntBigHeal--;
                        wait(0);
                    }
				}; break;
				case '6': /// Big armor (+20 armor, -10% hp)
				{
                    if (cntBigArmor < 1 || round(playerBasic.health * 0.1) >= playerCurent.health)
                    {
                        writeError();
                    }
                    else
                    {
                        playerCurent.armor += 20*deltArmor;
                        playerCurent.health -= round(playerBasic.health*0.1);

                        if(!fury && playerCurent.health <= round(playerBasic.health * 0.1))
                        {
                            fury = 1;

                            playerCurent.attack = round(playerCurent.attack * 1.5);
                            playerCurent.armor = round(playerCurent.armor * 1.5);
                            playerCurent.luck += deltLuck;
                        }

                        cntBigArmor--;
                        wait(0);
                    }
				}; break;
				case '7': /// Big attack (+25% attack, -2 luck)
				{
                    if (cntBigAttack < 1 || playerCurent.luck < 3*deltLuck)
                    {
                        writeError();
                    }
                    else
                    {
                        playerCurent.attack += round(playerBasic.attack * 0.25);
                        playerCurent.luck -= 2*deltLuck;

                        cntBigAttack--;
                        wait(0);
                    }
				}; break;
				case '8': /// Big luck (+5 luck, -10% attack)
				{
                    if (cntBigLuck < 1)
                    {
                        writeError();
                    }
                    else
                    {
                        playerCurent.luck += 5*deltLuck;
                        playerCurent.attack -= round(playerBasic.attack * 0.1);

                        cntBigLuck--;
                        wait(0);
                    }
				}; break;
				case 'b': return; break;
				default: writeError(); break;
            }
        }
    }

    public: inline void chooseChest(bool rare)
    {
        wait(0);

        char input;
        srand(time(0));

        while (1)
        {
            for (ll i = 0; i < chest.sz; i++)
            {
                cout << chest[i] << "\n";
            }

            input = getch();

            if (input == 'l' || input == 'r' || input == 'm')
            {
                ll val;

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
                    wait();

                    if(rare)
                    {
                        cntSmallHeal++;
                        cout << "You got one more SMALL HEAL potion\n";
                    }else
                    {
                        cntBigHeal++;
                        cout << "You got one more BIG HEAL potion\n";
                    }

                    wait(1500);

                    return;
                }else
                if (val%4 == 1)
                {
                    wait();

                    if(rare)
                    {
                        cntSmallArmor++;
                        cout << "You got one more SMALL ARMOR potion\n";
                    }else
                    {
                        cntBigArmor++;
                        cout << "You got one more BIG ARMOR potion\n";
                    }

                    wait(1500);

                    return;
                }else
                if (val%4 == 2)
                {
                    wait();

                    if(rare)
                    {
                        cntSmallAttack++;
                        cout << "You got one more SMALL ATTACK potion\n";
                    }else
                    {
                        cntBigAttack++;
                        cout << "You got one more BIG ATTACK potion\n";
                    }

                    wait(1500);

                    return;
                }else
                if (val%4 == 3)
                {
                    wait();

                    if(rare)
                    {
                        cntSmallLuck++;
                        cout << "You got one more SMALL LUCK potion\n";
                    }else
                    {
                        cntBigLuck++;
                        cout << "You got one more BIG LUCK potion\n";
                    }

                    wait(1500);

                    return;
                }
            }
            else
            {
                writeError();
            }
        }
    }

    public: inline void setPotionsForMultiplayer()
    {
        cntSmallArmor = 2;
        cntSmallAttack = 2;
        cntSmallHeal = 2;
        cntSmallLuck = 2;

        cntBigArmor = 1;
        cntBigAttack = 1;
        cntBigHeal = 1;
        cntBigLuck = 1;
    }
};

Inventory inventory;

inline ll menu(ll nexLevel)
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
		cout << "\tm - multiplayer (new)\n";
		cout << "\te - exit\n";

		char input = getch();

		switch (input)
		{
            case 'n': return 1; break;
            case 'u': return 2; break;
            case 'm': return 3; break;
            case 'e': myExit(0); break;
            default: writeError(); break;
		}
	}
}

inline ll updateStats()
{
	char input;
	pers playerCopy = player;

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

		cout << "\tr - redone (only this session of updating)\n\n";

		cout << "Press to continue:\n";
		cout << "\tn - next battle\n";
		cout << "\tm - menu\n";
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
                    player.health += deltHealth;
                    wait(0);
                }
            }; break;
            case '2':
            {
                if (player.talant < 3 || player.armor == 50*deltArmor)
                {
                    writeError();
                }
                else
                {
                    player.talant -= 3;
                    player.armor += 3*deltArmor;

                    if(player.armor > 50*deltArmor)
                    {
                        player.talant += player.armor - 50*deltArmor;
                        player.armor = 50*deltArmor;
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
                    player.attack += deltAttack;
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
                    player.luck += deltLuck;
                    wait(0);
                }
            }; break;
            case 'r':
            {
                player = playerCopy;

                wait(0);
            }; break;
            case 'n': return 1; break;
            case 'm': return 0; break;
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

inline void move(pers player, ll pos1, pers mob, ll pos2, ll level, bool fury1, bool fury2 = 0, bool turn = 0, bool multiplayer = 0)
{
	wait(100);

	if(!multiplayer)
    {
        cout << "Level: " << level << "\n\n";
	}

	player.writePicture(pos1);
	player.writeStats(fury1);
	mob.writePicture(pos2);
	mob.writeStats(fury2);

	return;
}

inline bool fight(ll level)
{
	char input;

	bool fury = 0;

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
                move(playerLocal, 2, mobLocal, 2, level, fury);
                move(playerLocal, 1, mobLocal, 2, level, fury);
                mobLocal.calcDamage(playerLocal.calcAttack());
                move(playerLocal, 2, mobLocal, 2, level, fury);

                if (mobLocal.health == 0)
                {
                    return 1;
                }

                playerLocal.mana++;
            }; break;
            case 'd':
            {
                move(playerLocal, 2, mobLocal, 2, level, fury);
                move(playerLocal, 3, mobLocal, 2, level, fury);
                playerLocal.defense();
                move(playerLocal, 2, mobLocal, 2, level, fury);

                playerLocal.mana += 2;
            }; break;
            case 'i':
            {
                inventory.usingPotion(player, playerLocal, fury);
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
                    mobLocal.health -= min(mobLocal.health, 750ll);

                    wait(0);

                    if (mobLocal.health == 0)
                    {
                        return 1;
                    }

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

                    playerLocal.luck += 3*deltLuck;

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
			move(playerLocal, 2, mobLocal, 2, level, fury);
			move(playerLocal, 2, mobLocal, 3, level, fury);
			mobLocal.defense();
			move(playerLocal, 2, mobLocal, 2, level, fury);
			wait(0);
		}
		else
		{
			move(playerLocal, 2, mobLocal, 2, level, fury);
			move(playerLocal, 2, mobLocal, 1, level, fury);
			playerLocal.calcDamage(mobLocal.calcAttack());
			move(playerLocal, 2, mobLocal, 2, level, fury);
			wait(0);

			if (playerLocal.health == 0)
			{
				return 0;
			}
			if (playerLocal.health <= round(player.health * 0.1) && !fury)
			{
				fury = 1;
				playerLocal.attack = round(playerLocal.attack * 1.5);
				playerLocal.armor = round(playerLocal.armor * 1.5);
				playerLocal.luck += deltLuck;
			}
		}
	}
}

inline void hello()
{
	cout << "\tConsole Dungeon (V-0.3.0)\n\n";
	cout << "Creators:\n";
	cout << "\tIdea:\n";
	cout << "\t\tBugInSystem\n";
	cout << "\tCode:\n";
	cout << "\t\tBagInCode\n";
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
	ll typeOfArmor;

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

		cout << "You want to begin with count of Small Heal potion: ";
		cin >> inventory.cntSmallHeal;
		cout << "\n";

		cout << "You want to begin with count of Small Armor potion: ";
		cin >> inventory.cntSmallArmor;
		cout << "\n";

		cout << "You want to begin with count of Small Attack potion: ";
		cin >> inventory.cntSmallAttack;
		cout << "\n";

		cout << "You want to begin with count of Small Luck potion: ";
		cin >> inventory.cntSmallLuck;
		cout << "\n";

		cout << "You want to begin with count of Big Heal potion: ";
		cin >> inventory.cntBigHeal;
		cout << "\n";

		cout << "You want to begin with count of Big Armor potion: ";
		cin >> inventory.cntBigArmor;
		cout << "\n";

		cout << "You want to begin with count of Big Attack potion: ";
		cin >> inventory.cntBigAttack;
		cout << "\n";

		cout << "You want to begin with count of Big Luck potion: ";
		cin >> inventory.cntBigLuck;
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
	ll stat, tlvl;
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
		if (type == "health"  && stat > 0 && stat % deltHealth == 0)
		{
			per.health = stat;
		}
		else { cinf.close(); return false; }
	}
	else { cinf.close(); return false; }

	if (cinf >> type >> stat)
	{
		if (type == "armor"  && stat >= 0 && stat <= 50 * deltArmor && stat % deltArmor == 0)
		{
			per.armor = stat;
		}
		else { cinf.close(); return false; }
	}
	else { cinf.close(); return false; }

	if (cinf >> type >> stat)
	{
		if (type == "luck"  && stat > 0 && stat % deltLuck == 0)
		{
			per.luck = stat;
		}
		else { cinf.close(); return false; }
	}
	else { cinf.close(); return false; }

	if (cinf >> type >> stat)
	{
		if (type == "attack"  && stat > 0 && stat % deltAttack == 0)
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
		if (type == "cntSmallHeal" && stat >= 0)
		{
			inv.cntSmallHeal = stat;
		}
		else { cinf.close(); return false; }
	}
	else { cinf.close(); return false; }

	if (cinf >> type >> stat)
	{
		if (type == "cntSmallArmor" && stat >= 0)
		{
			inv.cntSmallArmor = stat;
		}
		else { cinf.close(); return false; }
	}
	else { cinf.close(); return false; }

	if (cinf >> type >> stat)
	{
		if (type == "cntSmallLuck" && stat >= 0)
		{
			inv.cntSmallLuck = stat;
		}
		else { cinf.close(); return false; }
	}
	else { cinf.close(); return false; }

	if (cinf >> type >> stat)
	{
		if (type == "cntSmallAttack" && stat >= 0)
		{
			inv.cntSmallAttack = stat;
		}
		else { cinf.close(); return false; }
	}
	else { cinf.close(); return false; }

	if (cinf >> type >> stat)
	{
		if (type == "cntBigHeal" && stat >= 0)
		{
			inv.cntBigHeal = stat;
		}
		else { cinf.close(); return false; }
	}
	else { cinf.close(); return false; }

	if (cinf >> type >> stat)
	{
		if (type == "cntBigArmor" && stat >= 0)
		{
			inv.cntBigArmor = stat;
		}
		else { cinf.close(); return false; }
	}
	else { cinf.close(); return false; }

	if (cinf >> type >> stat)
	{
		if (type == "cntBigLuck" && stat >= 0)
		{
			inv.cntBigLuck = stat;
		}
		else { cinf.close(); return false; }
	}
	else { cinf.close(); return false; }

	if (cinf >> type >> stat)
	{
		if (type == "cntBigAttack" && stat >= 0)
		{
			inv.cntBigAttack = stat;
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
	string nick;
	pers per;
	Inventory invent;

	cout << "Write your nickname and press enter:\n";
	while (1)
	{
		getline(cin, nick);
		if (nick != "")
		{
			break;
		}
	}
	for (auto &it : nick)
	{
		if (it == ' ')
		{
			it = '_';
		}
	}
	per.setNickName(nick);

	if (tryLoad(invent, per))
	{
		cout << "Save loaded\nDo you want to continue previous game? If yes - press '1', else press '0'\n";
		while (1)
		{
			input = getch();
			if (input == '0')
			{
				level = 1;
				player.setNickName(nick);
				break;
			}
			else if (input == '1')
			{
				player = per;
				inventory = invent;
				player.setNickName(nick);
				break;
			}
		}
	}
	else
	{
		player.setNickName(nick);
		cout << "No save with this name\nPress any key to continue";
		getch();
	}

	wait();

}

void myExit(ll inf=0)
{
	ofstream coutf(player.nickName + ".sf");

	coutf << "level " << level << "\n";
	coutf << "health " << player.health << "\n";
	coutf << "armor " << player.armor << "\n";
	coutf << "luck " << player.luck << "\n";
	coutf << "attack " << player.attack << "\n";
	coutf << "typeArmor " << player.typeArmor << "\n";
	coutf << "talant " << player.talant << "\n";
	coutf << "cntSmallHeal " << inventory.cntSmallHeal << "\n";
	coutf << "cntSmallArmor " << inventory.cntSmallArmor << "\n";
	coutf << "cntSmallLuck " << inventory.cntSmallLuck << "\n";
	coutf << "cntSmallAttack " << inventory.cntSmallAttack << "\n";
	coutf << "cntBigHeal " << inventory.cntBigHeal << "\n";
	coutf << "cntBigArmor " << inventory.cntBigArmor << "\n";
	coutf << "cntBigLuck " << inventory.cntBigLuck << "\n";
	coutf << "cntBigAttack " << inventory.cntBigAttack << "\n";

	coutf.close();

	exit(inf);
}

void win(const string & nickName, const string & resultFirst, const string & resultSecond)
{
    wait(0);

    cout << nickName << " win this round!\n\n";

    cout << resultFirst << "\n";

    for(int i = 0; i < resultFirst.sz; i++)
    {
        cout << "-";
    }
    cout << "|\n";

    cout << resultSecond << "\n\n";

    cout << "Press any key to continue\n";
    getch();

    wait(0);

    return;
}

bool endOfGame(const string & nickName, const string & resultFirst, const string & resultSecond)
{
    wait(0);

    char input;

    cout << nickName << " win the battle!\n\n";

    cout << resultFirst << "\n";

    for(int i = 0; i < resultFirst.sz; i++)
    {
        cout << "-";
    }
    cout << "|\n";

    cout << resultSecond << "\n\n";

    cout << "Do you want to continue multiplayer?\n";
    cout << "\ty - yes\n";
    cout << "\tn - no\n";

    input = getch();

    while(1)
    {
        switch(input)
        {
            case 'y':
            {
                wait(0);
                return 1;
            };break;
            case 'n':
            {
                wait(0);
                return 0;
            };break;
            default : writeError(); break;
        }

        cout << "Do you want to continue multiplayer? (there is no turning back):\n";
        cout << "\ty - yes\n";
        cout << "\tn - no\n";

        input = getch();
    }
}

void multiplayer()
{
    char input;

    wait();

    while(1)
    {
        pers Player1, curentPlayer1;
        pers Player2, curentPlayer2;
        Inventory inv1, inv2;

        string nickName, resultFirst, resultSecond;

        Player1.makePicture(LightArmorBase, LightArmorAttack, LightArmorDefense, 2);
        Player2.makePicture(LightArmorBase, LightArmorAttack, LightArmorDefense, 2);

        inv1.setPotionsForMultiplayer();
        inv2.setPotionsForMultiplayer();

        getline(cin, nickName);

        cout << "Write please nick of first player: ";
        getline(cin, nickName);

        if(nickName == "")
        {
            nickName = "Player1";
        }

        Player1.setNickName(nickName);
        resultFirst = nickName;

        cout << "Write please nick of second player: ";
        getline(cin, nickName);

        if(nickName == "")
        {
            nickName = "Player2";
        }

        Player2.setNickName(nickName);
        resultSecond = nickName;

        while(resultFirst.sz != resultSecond.sz)
        {
            if(resultFirst.sz < resultSecond.sz)
            {
                resultFirst = resultFirst + " ";
            }else
            {
                resultSecond = resultSecond + " ";
            }
        }

        resultFirst = resultFirst + ": ";
        resultSecond = resultSecond + ": ";

        while(Player1.health && Player2.health)
        {
            wait(0);

            bool fury1 = 0;
            bool fury2 = 0;

            curentPlayer1 = Player1;
            curentPlayer2 = Player2;

            srand(time(0));
            bool turn = rand()%2;

            while(1)
            {
                curentPlayer1.writePicture(2);
                curentPlayer1.writeStats(fury1);

                curentPlayer2.writePicture(2);
                curentPlayer2.writeStats(fury2);

                if(turn)
                {
                    cout << "IT IS YOUR TURN, " << curentPlayer1.nickName << "\n\n";
                }else
                {
                    cout << "IT IS YOUR TURN, " << curentPlayer2.nickName << "\n\n";
                }

                cout << "Press to continue:\n";
                cout << "\ta - attack\n";
                cout << "\td - defense\n";
                cout << "\tq - Holly Sword (make 75 damage, cost 10 mana)\n";
                cout << "\te - Gods` Pleasure (add 3 luck, cost 10 mana)\n";
                cout << "\ti - inventory\n";

                input = getch();

                if(input == 'a')
                {
                    move(curentPlayer1, 2, curentPlayer2, 2, 0, fury1, fury2, turn, 1);

                    if(turn)
                    {
                        move(curentPlayer1, 1, curentPlayer2, 2, 0, fury1, fury2, turn, 1);
                        curentPlayer2.calcDamage(curentPlayer1.calcAttack());
                        curentPlayer1.mana ++;

                        if(curentPlayer2.health == 0)
                        {
                            Player1.health -= 1000;

                            resultFirst = resultFirst + "I";
                            resultSecond = resultSecond + "O";

                            win(Player1.nickName, resultFirst, resultSecond);

                            break;
                        }else
                        if(curentPlayer2.health < round(Player2.health * 0.1) && !fury2)
                        {
                            fury2 = 1;

                            curentPlayer2.armor *= 1.5;
                            curentPlayer2.attack *= 1.5;
                            curentPlayer2.luck += deltLuck;
                        }
                    }else
                    {
                        move(curentPlayer1, 2, curentPlayer2, 1, 0, fury1, fury2, turn, 1);
                        curentPlayer1.calcDamage(curentPlayer2.calcAttack());
                        curentPlayer2.mana ++;

                        if(curentPlayer1.health == 0)
                        {
                            Player2.health -= 1000;

                            resultFirst = resultFirst + "O";
                            resultSecond = resultSecond + "I";

                            win(Player2.nickName, resultFirst, resultSecond);

                            break;
                        }else
                        if(curentPlayer1.health < round(Player1.health * 0.1) && !fury1)
                        {
                            fury1 = 1;

                            curentPlayer1.attack *= 1.5;
                            curentPlayer1.armor *= 1.5;
                            curentPlayer1.luck += deltLuck;
                        }
                    }

                    move(curentPlayer1, 2, curentPlayer2, 2, 0, fury1, fury2, turn, 1);

                    wait();

                    turn = !turn;
                }else
                if(input == 'd')
                {
                    move(curentPlayer1, 2, curentPlayer2, 2, 0, fury1, fury2, turn, 1);

                    if(turn)
                    {
                        move(curentPlayer1, 3, curentPlayer2, 2, 0, fury1, fury2, turn, 1);
                        curentPlayer1.defense();
                        curentPlayer1.mana += 2;
                    }else
                    {
                        move(curentPlayer1, 2, curentPlayer2, 3, 0, fury1, fury2, turn, 1);
                        curentPlayer2.defense();
                        curentPlayer2.mana += 2;
                    }

                    move(curentPlayer1, 2, curentPlayer2, 2, 0, fury1, fury2, turn, 1);

                    wait();

                    turn = !turn;
                }else
                if(input == 'i')
                {
                    if(turn)
                    {
                        inv1.usingPotion(Player1, curentPlayer1, fury1);
                    }else
                    {
                        inv2.usingPotion(Player2, curentPlayer2, fury2);
                    }

                    wait(0);
                    continue;
                }else
                if(input == 'q')
                {
                    if(turn)
                    {
                        if (curentPlayer1.mana < 10)
                        {
                            writeError();
                            continue;
                        }
                        else
                        {
                            curentPlayer1.mana -= 10;
                            curentPlayer2.health -= min(curentPlayer2.health, 750ll);

                            wait(0);

                            if(curentPlayer2.health == 0)
                            {
                                Player1.health -= 1000;

                                resultFirst = resultFirst + "I";
                                resultSecond = resultSecond + "O";

                                win(Player1.nickName, resultFirst, resultSecond);

                                break;
                            }else
                            if(curentPlayer2.health < round(Player2.health * 0.1) && !fury2)
                            {
                                fury2 = 1;

                                curentPlayer2.armor *= 1.5;
                                curentPlayer2.attack *= 1.5;
                                curentPlayer2.luck += deltLuck;
                            }

                            wait(0);

                            continue;
                        }
                    }else
                    {
                        if (curentPlayer2.mana < 10)
                        {
                            writeError();
                            continue;
                        }
                        else
                        {
                            curentPlayer2.mana -= 10;
                            curentPlayer1.health -= min(curentPlayer2.health, 750ll);

                            wait(0);

                            if(curentPlayer1.health == 0)
                            {
                                Player1.health -= 1000;

                                resultFirst = resultFirst + "O";
                                resultSecond = resultSecond + "I";

                                win(Player2.nickName, resultFirst, resultSecond);

                                break;
                            }else
                            if(curentPlayer1.health < round(Player1.health * 0.1) && !fury1)
                            {
                                fury1 = 1;

                                curentPlayer1.armor *= 1.5;
                                curentPlayer1.attack *= 1.5;
                                curentPlayer1.luck += deltLuck;
                            }

                            wait(0);

                            continue;
                        }
                    }
                }else
                if(input == 'e')
                {
                    if(turn)
                    {
                        if(curentPlayer1.mana < 10)
                        {
                            writeError();
                            continue;
                        }else
                        {
                            curentPlayer1.mana -= 10;
                            curentPlayer1.luck += 3*deltLuck;

                            wait(0);

                            continue;
                        }
                    }else
                    {
                        if(curentPlayer2.mana < 10)
                        {
                            writeError();
                            continue;
                        }else
                        {
                            curentPlayer2.mana -= 10;
                            curentPlayer2.luck += 3*deltLuck;

                            wait(0);

                            continue;
                        }
                    }
                }else
                {
                    writeError();
                    continue;
                }
            }
        }

        if(Player1.health)
        {
            if(!endOfGame(Player1.nickName, resultFirst, resultSecond))
            {
                return;
            }
        }else
        {
            if(!endOfGame(Player2.nickName, resultFirst, resultSecond))
            {
                return;
            }
        }
    }
}

int main()
{
	player.makePicture(WithoutArmorBase, WithoutArmorAttack, WithoutArmorDefense, 0);

	hello();
	askPreviousSave();
	cheat();

	ll function = 0;

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
                    inventory.chooseChest(level % 20);
                }

                level += x;

                if (x && level % 5 == 0) player.talant++; else
                if (x && level % 20 == 1) player.talant += 3; else
                if (x && level % 5 == 1) player.talant++;

                function = 0;
            }; break;
            case 2: function = updateStats(); break;
            case 3:
            {
                function = 0;
                multiplayer();
            };
		}
	}
}
