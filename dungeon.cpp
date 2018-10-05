#include "setup.txt"

bool fury;

struct Pictures
{
    vector < string > pictureBasick;
    vector < string > pictureAttack;
    vector < string > pictureDefense;
};

class pers
{
    public: int health = 1000;
    public: int armor = 0;
    public: int luck = 1;
    public: int attack = 100;
    public: int typeArmor = 0;
    public: int talant = 0;
    public: int mana = 0;

    public: Pictures pictures;

    public: inline void makePicture(vector < string > Basick, vector < string > Attack, vector < string > Defense, int type)
    {
        pictures.pictureAttack = Attack;
        pictures.pictureBasick = Basick;
        pictures.pictureDefense = Defense;

        armor -= typeArmor;
        typeArmor = type;
        armor += typeArmor;

        return;
    }

    public: inline void writePicture(int typePicture)
    {
        if(typePicture == 1)
        {
            for(int i = 0; i < pictures.pictureAttack.sz; i++)
            {
                cout << pictures.pictureAttack[i] << "\n";
            }
        }else
        if(typePicture == 2)
        {
            for(int i = 0; i < pictures.pictureBasick.sz; i++)
            {
                cout << pictures.pictureBasick[i] << "\n";
            }
        }else
        {
            for(int i = 0; i < pictures.pictureDefense.sz; i++)
            {
                cout << pictures.pictureDefense[i] << "\n";
            }
        }

        return;
    }

    public: inline void writeStats(bool fury = 0)
    {
        cout << "------------------------|\n";

        if(fury) cout << "\t(fury)\n";

        cout << "health (armor): " << health << " (" << armor << ")\n";
        cout << "attack (luck):  " << attack << " (" << luck << ")\n";
        cout << "mana: ";

        for(int i = 1; i <= mana; i++)
        {
            cout << '*';

            if(i%5 == 0) cout << ' ';
        }

        cout << "\n\n";

        return;
    }

    public: inline int calcAttack()
    {
        srand(time(0));

        int valAttack;
        int maxPersent = 0;

        for(int i = 1; i <= luck; i++)
        {
            maxPersent = max(maxPersent, (rand()%101));
        }

        valAttack = (attack*maxPersent)/100;

        return valAttack;
    }

    public: void calcDamage(int valAttack)
    {
        valAttack = ((100 - armor)*valAttack)/100;

        health = health - min(health, valAttack);

        return;
    }

    public: void generateMob(int level)
    {
        health += 10 * (level-1);
        armor += level/20*3;
        attack += (level/5)*10;
        luck += level/20;

        if(level % 20 == 0)
        {
            health *= 1.25;
            armor *= 1.25;
            attack *= 1.25;
            luck *= 1.25;

            makePicture(LegendarySkeletonBase, LegendarySkeletonAttack, LegendarySkeletonDefense, 0);
        }else
        if(level % 5 == 0)
        {
            health *= 1.15;
            armor *= 1.15;
            attack *= 1.15;
            luck *= 1.15;

            makePicture(RareSkeletonBase, RareSkeletonAttack, RareSkeletonDefense, 0);
        }else
        {
            makePicture(SkeletonBase, SkeletonAttack, SkeletonDefense, 0);
        }

        return;
    }

    public: void defense()
    {
        luck++;
        return;
    }
};

class Inventory
{
    public: int cntHeal = 0;
    public: int cntArmor = 0;
    public: int cntLuck = 0;
    public: int cntAttack = 0;

    public: bool heavyArmor = 0;
    public: bool middleArmor = 0;
    public: bool lightArmor = 0;

    inline void potion(pers & playerBasic, pers & playerCurent)
    {
        char input;

        wait(0);

        while(1)
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
                    if(cntHeal < 1)
                    {
                        writeError();
                    }else
                    {
                        playerCurent.health += playerBasic.health * 0.10;

                        if(fury)
                        {
                            fury = 0;
                            playerCurent.attack /= 1.5;
                            playerCurent.armor /= 1.5;
                            playerCurent.luck --;
                        }

                        cntHeal --;
                        wait(0);
                    }
                }; break;
                case '2':
                {
                    if(cntArmor < 1)
                    {
                        writeError();
                    }else
                    {
                        playerCurent.armor += 2;
                        cntArmor --;
                        wait(0);
                    }
                }; break;
                case '3':
                {
                    if(cntAttack < 1)
                    {
                        writeError();
                    }else
                    {
                        playerCurent.attack +=  playerBasic.attack * 0.10;
                        cntAttack --;
                        wait(0);
                    }
                };break;
                case '4':
                {
                    if(cntLuck < 1)
                    {
                        writeError();
                    }else
                    {
                        playerCurent.luck += 2;
                        cntLuck --;
                        wait(0);
                    }
                };break;
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

        while(1)
        {
            for(int i = 0; i < chest.sz; i++)
            {
                cout << chest[i] << "\n";
            }

            input = getch();

            if(input == 'l' || input == 'r' || input == 'm')
            {
                int val = rand()%4;

                if(val == 0)
                {
                    cntHeal++;

                    wait(0);
                    cout << "You got one more HEAL potion\n";
                    wait(2000);

                    return;
                }
                if(val == 1)
                {
                    cntArmor++;

                    wait(0);
                    cout << "You got one more ARMOR potion\n";
                    wait(2000);

                    return;
                }
                if(val == 2)
                {
                    cntAttack++;

                    wait(0);
                    cout << "You got one more ATTACK potion\n";
                    wait(2000);

                    return;
                }
                if(val == 3)
                {
                    cntLuck++;

                    wait(0);
                    cout << "You got one more LUCK potion\n";
                    wait(2000);

                    return;
                }
            }else
            {
                writeError();
            }
        }
    }
};

pers player, mob;
Inventory inventory;

inline int menu(int nexLevel)
{
    wait(0);

    while(1)
    {
        cout << "Next level: " << nexLevel;

        if(nexLevel % 20 == 0)
        {
            cout << " - LEGENDARY\n\n";
        }else
        if(nexLevel % 5 == 0)
        {
            cout << " - Rare\n\n";
        }else
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
            case 'e': exit(0); break;
            default: writeError(); break;
        }
    }
}

inline int updateStats()
{
    char input;

    wait(0);

    while(1)
    {
        player.writePicture(2);
        player.writeStats();

        cout << "\nYou have " << player.talant << " talant(s)\n\n";
        cout << "Press to update:\n";
        cout << "\t1 - +100 health (cost 1 talant)\n";
        cout << "\t2 -   +3  armor (cost 3 talant)\n";
        cout << "\t3 -  +10 attack (cost 1 talant)\n";
        cout << "\t4 -   +1   luck (cost 3 talant)\n\n";

        cout << "Press to continue:\n";
        cout << "\tn - next battle\n";
        cout << "\tm - menu\n";
        ///cout << "\tc - change weapon\n";        ### change weapon
        cout << "\te - exit\n";

        input = getch();

        switch(input)
        {
            case '1':
            {
                if(player.talant < 1)
                {
                    writeError();
                }else
                {
                    player.talant--;
                    player.health += 100;
                    wait(0);
                }
            }; break;
            case '2':
            {
                if(player.talant < 3)
                {
                    writeError();
                }else
                {
                    player.talant -= 3;
                    player.armor += 3;
                    wait(0);
                }
            }; break;
            case '3':
            {
                if(player.talant < 1)
                {
                    writeError();
                }else
                {
                    player.talant--;
                    player.attack += 10;
                    wait(0);
                }
            }; break;
            case '4':
            {
                if(player.talant < 3)
                {
                    writeError();
                }else
                {
                    player.talant -= 3;
                    player.luck ++;
                    wait(0);
                }
            }; break;
            case 'n': return 1; break;
            case 'm': return 0; break;
            ///case 'c': return 2; break;        ### change weapon
            case 'e': exit(0); break;
            default: writeError(); break;
        }
    }
}

inline void writeFinalBattleWords(bool win)
{
    wait(0);

    if(win)
    {
        cout << "\tYOU WIN!!!\n\n";
    }else
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

    while(1)
    {
        cout << "Level: " << level << "\n\n";
        playerLocal.writePicture(2);
        playerLocal.writeStats(fury);
        mobLocal.writePicture(2);
        mobLocal.writeStats();

        cout << "Press to continue:\n";
        cout << "\ta - attack\n";
        cout << "\td - defense\n";
        cout << "\tq - make 50 extra damage (cost 5 mana)\n";
        cout << "\te - make 2 extra luck (cost 5 mana)\n";
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

                if(mobLocal.health == 0) return 1;

                playerLocal.mana ++;
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
                if(playerLocal.mana < 5)
                {
                    writeError();
                    continue;
                }else
                {
                    playerLocal.mana -= 5;
                    mobLocal.health -= min(mobLocal.health, 50);

                    wait(0);

                    if(mobLocal.health == 0) return 1;

                    continue;
                }
            }; break;
            case 'e':
            {
                if(playerLocal.mana < 5)
                {
                    writeError();
                    continue;
                }else
                {
                    playerLocal.mana -= 5;

                    playerLocal.luck += 2;

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

        input = rand()%8;

        if(input == 0)
        {
            move(playerLocal, 2, mobLocal, 2, level);
            move(playerLocal, 2, mobLocal, 3, level);
            mobLocal.defense();
            move(playerLocal, 2, mobLocal, 2, level);
            wait(0);
        }else
        {
            move(playerLocal, 2, mobLocal, 2, level);
            move(playerLocal, 2, mobLocal, 1, level);
            playerLocal.calcDamage(mobLocal.calcAttack());
            move(playerLocal, 2, mobLocal, 2, level);
            wait(0);

            if(playerLocal.health == 0)
            {
                return 0;
            }
            if(playerLocal.health <= player.health * 0.1 && !fury)
            {
                fury = 1;
                playerLocal.attack *= 1.5;
                playerLocal.armor *= 1.5;
                playerLocal.luck ++;
            }
        }
    }
}

inline void help()
{
    wait(0);

    cout << "Welcome to my game!\n";
    cout << "In this game you have 4 stats: health, attack, armor and luck. On start you have 1000 health, 100 attack, 0 armor and 1 luck. Each stat can be updated by talant, which you get in battle with mobs.\n";
    cout << "There are unlimited count of levels. On each of them you met one mob in battle. Each next mob will be harder then previous. But there are 3 types of mobs: standard, rare and legendary.\n";
    cout << "Stats of mobs generate by next rules: on each next level standard mob get +10 health, on each 5th level - +10 attack, on each 20th level - +1 luck and armor. But you have to multiply all stat of standard mob on 1.15 for get stats of rare, and multiply on 1.25 to get stats of legendary\n";
    cout << "If you defeat 4 standard bot - you get 1 talant, if you defeat rare - you get 1 talant and if you defeat legendary - you get 3 talant\n";
    cout << "After each 5th win you get 3 chest with potion. But you have to choose one of them and you get the potion that is inside of your chest. This potion can update one of you stats on one battle. After finish your stats become normal again\n";
    cout << "In battle you have to decide: attack or defense? If you pick attack then computer generate random value x from 0 to 100. Computer generate it as more times as you have luck and get on result maximum of all this x. Then your attack is calculated by formula: ((your_attack)*(x%))*((100-opponent_armor)%). If you pick defense than you make no attack, but you get +1 t your luck.\n";
    cout << "That`s all. Press any key to begin\n";

    getch();

    wait(0);

    return;
}

inline void hello()
{
    cout << "\tConsole Dungeon\n\n";
    cout << "Creator:\n";
    cout << "\tBagInCode\n";
    cout << "\tBugInSystem\n";
    cout << "\tReeWorld\n";
    cout << "\tTheDarkness\n\n";
    cout << "Please, check that your console is full screen\n";
    cout << "If you need help - press \'h\', if not - press any other key\n";

    char input = getch();

    if(input == 'h') help();

    return;
}

int level = 1;

void cheat()
{
    string password;

    wait(0);

    cout << "If you are developer or tester, please enter developers password\n(looking for password in code of game, function \'cheat\'):\n";
    cin >> password;
    cout << "\n";

    if(password == "Julick_ne_voruy")
    {
        cout << "You want to begin from level: ";
        cin >> level;
        cout << "\n";

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
    }else
    {
        cout << "Password is incorrect\n";
        cout << "Press any key to continue\n";
        getch();
    }

    return;
}

main()
{
    player.makePicture(LightArmorBase, LightArmorAttack, LightArmorDefense, 0);

    hello();
    cheat();
    int function = 0;

    while(1)
    {
        switch (function)
        {
            case 0: function = menu(level); break;
            case 1:
            {
                bool x = fight(level);
                writeFinalBattleWords(x);
                level += x;

                if(x && level % 5 == 1)
                {
                    inventory.chooseChest();
                }

                if(x && level % 5 == 0) player.talant++; else
                if(x && level % 20 == 1) player.talant += 3; else
                if(x && level % 5 == 1) player.talant++;

                function = 0;
            }; break;
            case 2: function = updateStats(); break;
        }
    }
}
