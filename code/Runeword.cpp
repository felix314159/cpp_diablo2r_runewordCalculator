#include "Runeword.h"


vector<Runeword> runewords = {};

bool isUpper(char &c){
    // uppercase ASCII letter in A-Z
    if ((int)c > 64 && (int)c < 91){
        return true;
    }
    else {
        return false;
    }
}


// counts amount of uppercase letters in string
int calculateSockets(string &s){
    int amount = 0;
    for (char c: s){
        if (isUpper(c)){
            ++amount;
        }
    }
    return amount;
}


set<string> calculateRunes(string &s){
    set<string> final_set;
    // add "space" after every uppercase char, then
    // remove leading uppercases, then split by space
    string substring = "";
    int counter = 0;
    int length = s.length();
    for (char c: s){
        if (counter == 0){
            substring.push_back(c);
            ++counter;
        }
        else{
            if (isUpper(c)){
                final_set.insert(substring);
                substring = string("");
                substring.push_back(c);
            }
            else{
                substring.push_back(c);
            }

            ++counter;
        }

        // dont forget to add the last substring
        if (length == counter){
            final_set.insert(substring);
        }

    }

    return final_set;
}

void populate_runewords(vector<Runeword> &temp){

    Runeword ancients_pledge("Ancient's Pledge", "RalOrtTal",
                            set<string> {"Shields"},
                            "+50% Enhanced Defense\n"
                            "Cold Resist +43%\n"
                            "Fire Resist +48%\n"
                            "Lightning Resist +48%\n"
                            "Poison Resist +48%\n"
                            "10% Damage Goes To Mana\n\n"
                            "Lvl Requirement: 21", 21);

    Runeword authority("Authority", "HelShaelRal",
                            set<string> {"Body Armor"},
                            "2% Chance To Cast Level 10 Psychic Ward When Struck\n"
                            "10% Chance To Cast Level 15 Miasma Chain On Striking\n"
                            "+2 To Warlock Skill Levels\n"
                            "+40-60% Enhanced Damage\n"
                            "Requirements -15%\n"
                            "+20% Faster Hit Recovery\n"
                            "Fire Resist +30%\n\n"
                            "Lvl Requirement: 29", 29);

    Runeword beast("Beast", "BerTirUmMalLum",
                            set<string> {"Axes", "Hammers", "Scepters"},
                            "Level 9 Fanaticism Aura When Equipped\n"
                            "+40% Increased Attack Speed\n"
                            "+240-270% Enhanced Damage\n"
                            "20% Chance of Crushing Blow\n"
                            "25% Chance of Open Wounds\n"
                            "+3 To Werebear\n"
                            "+3 To Lycanthropy\n"
                            "Prevent Monster Heal\n"
                            "+25-40 To Strength\n"
                            "+10 To Energy\n"
                            "+2 To Mana After Each Kill\n"
                            "Level 13 Summon Grizzly (5 Charges)\n\n"
                            "Lvl Requirement: 63", 63);

    Runeword black("Black", "ThulIoNef",
                            set<string> {"Clubs", "Hammers", "Maces"},
                            "+120% Enhanced Damage\n"
                            "40% Chance of Crushing Blow\n"
                            "+200 to Attack Rating\n"
                            "Adds 3-14 Cold Damage for 3 seconds\n"
                            "+10 to Vitality\n"
                            "15% increased Attack Speed\n"
                            "Magic Damage Reduced by 2\n"
                            "Level 4 Corpse Explosion (12 charges)\n"
                            "Knockback\n\n"
                            "Lvl Requirement: 35", 35);

    Runeword bone("Bone", "SolUmUm",
                            set<string> {"Body Armor"},
                            "15% Chance To Cast Level 10 Bone Armor When Struck\n"
                            "15% Chance To Cast Level 10 Bone Spear On Striking\n"
                            "+2 To Necromancer Skill Levels\n"
                            "+100-150 To Mana (varies)\n"
                            "All Resistances +30\n"
                            "Damage Reduced By 7\n\n"
                            "Lvl Requirement: 47", 47);

    Runeword bramble("Bramble", "RalOhmSurEth",
                            set<string> {"Body Armor"},
                            "Level 15-21 Thorns Aura When Equipped\n"
                            "+50% Faster Hit Recovery\n"
                            "+25-50% To Poison Skill Damage\n"
                            "+300 Defense\n"
                            "Increase Maximum Mana 5%\n"
                            "Regenerate Mana 15%\n"
                            "+5% To Maximum Cold Resist\n"
                            "Fire Resist +30%\n"
                            "Poison Resist +100%\n"
                            "+13 Life After Each Kill\n"
                            "Level 13 Spirit of Barbs (33 Charges)\n\n"
                            "Lvl Requirement: 61", 61);

    Runeword brand("Brand", "JahLoMalGul",
                            set<string> {"Missile Weapons"},
                            "35% Chance To Cast Level 14 Amplify Damage When Struck\n"
                            "100% Chance To Cast Level 18 Bone Spear On Striking\n"
                            "+260-340% Enhanced Damage\n"
                            "Ignores Target's Defense\n"
                            "20% Bonus to Attack Rating\n"
                            "+280-330% Damage To Demons\n"
                            "20% Deadly Strike\n"
                            "Prevent Monster Heal\n"
                            "Knockback\n"
                            "Fires Explosive Arrows or Bolts [Level 15]\n\n"
                            "Lvl Requirement: 65", 65);

    Runeword breath_of_the_dying("Breath of the Dying", "VexHelElEldZodEth",
                            set<string> {"Weapons"},
                            "50% Chance To Cast Level 20 Poison Nova When You Kill An Enemy\n"
                            "Indestructible\n"
                            "+60% Increased Attack Speed\n"
                            "+350-400% Enhanced Damage (varies)\n"
                            "+200% Damage To Undead\n"
                            "-25% Target Defense\n"
                            "+50 To Attack Rating\n"
                            "+50 To Attack Rating Against Undead\n"
                            "7% Mana Stolen per Hit\n"
                            "12-15% Life Stolen per Hit\n"
                            "Prevent Monster Heal\n"
                            "+30 To All Attributes\n"
                            "+1 To Light Radius\n"
                            "Requirements -20%\n\n"
                            "Lvl Requirement: 69", 69);

    Runeword bulwark("Bulwark", "ShaelIoSol",
                            set<string> {"Helmets"},
                            "+20% Faster Hit Recovery\n"
                            "+4-6% Life stolen per hit\n"
                            "+75-100% Enhanced Defense\n"
                            "+10 to Vitality\n"
                            "Increase Maximum Life 5%\n"
                            "Replenish Life +30\n"
                            "Damage Reduced by 7\n"
                            "Physical Damage Received Reduced by 10-15%\n\n"
                            "Lvl Requirement: 35\n"
                            "LADDER/SINGLE-PLAYER ONLY.", 35);  // todo remove after new patch

    Runeword call_to_arms("Call to Arms", "AmnRalMalIstOhm",
                            set<string> {"Weapons"},
                            "+1 To All Skills\n"
                            "+40% Increased Attack Speed\n"
                            "+250-290% Enhanced Damage\n"
                            "Adds 5-30 Fire Damage\n"
                            "7% Life Stolen Per Hit\n"
                            "+2-6 To Battle Command\n"
                            "+1-6 To Battle Orders\n"
                            "+1-4 To Battle Cry\n"
                            "Prevent Monster Heal\n"
                            "Replenish Life +12\n"
                            "30% Better Chance of Getting Magic Items\n\n"
                            "Lvl Requirement: 57", 57);

    Runeword chains_of_honor("Chains of Honor", "DolUmBerIst",
                            set<string> {"Body Armor"},
                            "+2 To All Skills\n"
                            "+200% Damage To Demons\n"
                            "+100% Damage To Undead\n"
                            "8% Life Stolen Per Hit\n"
                            "+70% Enhanced Defense\n"
                            "+20 To Strength\n"
                            "Replenish Life +7\n"
                            "All Resistances +65\n"
                            "Damage Reduced By 8%\n"
                            "25% Better Chance of Getting Magic Items\n\n"
                            "Lvl Requirement: 63", 63);

    Runeword chaos("Chaos", "FalOhmUm",
                            set<string> {"Claws"},
                            "9% Chance To Cast Level 11 Frozen Orb On Striking\n"
                            "11% Chance To Cast Level 9 Charged Bolt On Striking\n"
                            "+35% Increased Attack Speed\n"
                            "+290-340% Enhanced Damage\n"
                            "Adds 216-471 Magic Damage\n"
                            "25% Chance of Open Wounds\n"
                            "+1 To Whirlwind\n"
                            "+10 To Strength\n"
                            "+15 Life After Each Demon Kill\n\n"
                            "Lvl Requirement: 57", 57);

    Runeword coven("Coven", "IstRalIo",
                            set<string> {"Helmets"},
                            "5% Chance To Cast Level 10 Sigil Lethargy When Struck\n"
                            "+1 To All Skills\n"
                            "+20% Faster Cast Rate\n"
                            "+30-50% Enhanced Defense\n"
                            "+1-5 Life After Each Kill\n"
                            "26-40% Better Chance Of Getting Magic Items\n"
                            "Fire Resist +30%\n"
                            "+10 to Vitality\n\n"
                            "Lvl Requirement: 51", 51);

    Runeword crescent_moon("Crescent Moon", "ShaelUmTir",
                            set<string> {"Axes", "Polearms", "Swords"},
                            "10% Chance To Cast Level 17 Chain Lightning On Striking\n"
                            "7% Chance To Cast Level 13 Static Field On Striking\n"
                            "+20% Increased Attack Speed\n"
                            "+180-220% Enhanced Damage\n"
                            "Ignore Target's Defense\n"
                            "-35% To Enemy Lightning Resist\n"
                            "25% Chance of Open Wounds\n"
                            "+9-11 Magic Absorb\n"
                            "+2 To Mana After Each Kill\n"
                            "Level 18 Summon Spirit Wolf (30 Charges)\n\n"
                            "Lvl Requirement: 47", 47);

    Runeword cure("Cure", "ShaelIoTal",
                            set<string> {"Helmets"},
                            "Level 1 Cleansing Aura when Equipped\n"
                            "+20% Faster Hit Recovery\n"
                            "+75-100% Enhanced Defense\n"
                            "+10 to Vitality\n"
                            "Increase Maximum Life 5%\n"
                            "Poison Resist +40-60%\n"
                            "Poison Length Reduced by 50%\n\n"
                            "Lvl Requirement: 35\n"
                            "LADDER/SINGLE-PLAYER ONLY.", 35);  // todo remove after new patch

    Runeword death("Death", "HelElVexOrtGul",
                            set<string> {"Swords", "Axes"},

                            "100% Chance To Cast Level 44 Chain Lightning When You Die\n"
                            "25% Chance To Cast Level 18 Glacial Spike On Attack\n"
                            "Indestructible\n"
                            "+300-385% Enhanced Damage\n"
                            "20% Bonus To Attack Rating\n"
                            "+50 To Attack Rating\n"
                            "Adds 1-50 Lightning Damage\n"
                            "7% Mana Stolen Per Hit\n"
                            "50% Chance of Crushing Blow\n"
                            "+(0.5 per Character Level) 0.5-49.5% Deadly Strike (Based on Character Level)\n"
                            "+1 To Light Radius\n"
                            "Level 22 Blood Golem (15 Charges)\n"
                            "Requirements -20%\n\n"
                            "Lvl Requirement: 55", 55);

    Runeword delirium("Delirium", "LemIstIo",
                            set<string> {"Helmets"},
                            "1% Chance To Cast Level 50 Delirium When Struck\n"
                            "6% Chance To Cast Level 14 Mind Blast When Struck\n"
                            "14% Chance To Cast Level 13 Terror When Struck\n"
                            "11% Chance To Cast Level 18 Confuse On Striking\n"
                            "+2 To All Skills\n"
                            "+261 Defense\n"
                            "+10 To Vitality\n"
                            "50% Extra Gold From Monsters\n"
                            "25% Better Chance of Getting Magic Items\n"
                            "Level 17 Attract (60 Charges)\n\n"
                            "Lvl Requirement: 51", 51);

    Runeword destruction("Destruction", "VexLoBerJahKo",
                            set<string> {"Polearms", "Swords"},
                            "23% Chance To Cast Level 12 Volcano On Striking\n"
                            "5% Chance To Cast Level 23 Molten Boulder On Striking\n"
                            "100% Chance To Cast level 45 Meteor When You Die\n"
                            "15% Chance To Cast Level 22 Nova On Attack\n"
                            "+350% Enhanced Damage\n"
                            "Ignore Target's Defense\n"
                            "Adds 100-180 Magic Damage\n"
                            "7% Mana Stolen Per Hit\n"
                            "20% Chance Of Crushing Blow\n"
                            "20% Deadly Strike\n"
                            "Prevent Monster Heal\n"
                            "+10 To Dexterity\n\n"
                            "Lvl Requirement: 65", 65);

    Runeword doom("Doom", "HelOhmUmLoCham",
                            set<string> {"Axes", "Hammers", "Polearms"},
                            "5% Chance To Cast Level 18 Volcano On Striking\n"
                            "Level 12 Holy Freeze Aura When Equipped\n"
                            "+2 To All Skills\n"
                            "+45% Increased Attack Speed\n"
                            "+330-370% Enhanced Damage\n"
                            "-(40-60)% To Enemy Cold Resist\n"
                            "20% Deadly Strike\n"
                            "25% Chance of Open Wounds\n"
                            "Prevent Monster Heal\n"
                            "Freezes Target +3\n"
                            "Requirements -20%\n\n"
                            "Lvl Requirement: 67", 67);

    Runeword dragon("Dragon", "SurLoSol",
                            set<string> {"Body Armor", "Shields"},
                            "20% Chance to Cast Level 18 Venom When Struck\n"
                            "12% Chance To Cast Level 15 Hydra On Striking\n"
                            "Level 14 Holy Fire Aura When Equipped\n"
                            "+360 Defense\n"
                            "+230 Defense vs. Missiles\n"
                            "+3-5 To All Attributes (varies)\n"
                            "+0.375-37.125 To Strength (Based on Character Level)\n"
                            "Increase Maximum Mana 5% (Armor Only)\n"
                            "+50 To Mana (Shields Only)\n"
                            "+5% To Maximum Lightning Resist\n"
                            "Damage Reduced by 7\n\n"
                            "Lvl Requirement: 61", 61);

    Runeword dream("Dream", "IoJahPul",
                            set<string> {"Helmets", "Shields"},
                            "10% Chance To Cast Level 15 Confuse When Struck\n"
                            "Level 15 Holy Shock Aura When Equipped\n"
                            "+20-30% Faster Hit Recovery\n"
                            "+30% Enhanced Defense\n"
                            "+150-220 Defense\n"
                            "+10 To Vitality\n"
                            "Increase Maximum Life 5% (Helms Only)\n"
                            "+50 To Life (Shields Only)\n"
                            "+0.625-61.875 To Mana (Based On Character Level)\n"
                            "All Resistances +5-20\n"
                            "12-25% Better Chance of Getting Magic Items\n\n"
                            "Lvl Requirement: 65", 65);

    Runeword duress("Duress", "ShaelUmThul",
                            set<string> {"Body Armor"},
                            "+40% Faster Hit Recovery\n"
                            "+10-20% Enhanced Damage\n"
                            "Adds 37-133 Cold Damage for 2 seconds\n"
                            "15% Chance of Crushing Blow\n"
                            "33% Chance of Open Wounds\n"
                            "+150-200% Enhanced Defense\n"
                            "-20% Slower Stamina Drain\n"
                            "Cold Resist +45%\n"
                            "Lightning Resist +15%\n"
                            "Fire Resist +15%\n"
                            "Poison Resist +15%\n\n"
                            "Lvl Requirement: 47", 47);

    Runeword edge("Edge", "TirTalAmn",
                            set<string> {"Missile Weapons"},
                            "Level 15 Thorns Aura When Equipped\n"
                            "+35% Increased Attack Speed\n"
                            "+320-380% Damage To Demons\n"
                            "+280% Damage To Undead\n"
                            "+75 Poison Damage for 5 seconds\n"
                            "7% Life Stolen Per Hit\n"
                            "Prevent Monster Heal\n"
                            "+5-10 To All Attributes\n"
                            "+2 To Mana After Each Kill\n"
                            "Reduces All Vendor Prices 15%\n\n"
                            "Lvl Requirement: 25", 25);

    Runeword enigma("Enigma", "JahIthBer",
                            set<string> {"Body Armor"},
                            "+2 To All Skills\n"
                            "+45% Faster Run/Walk\n"
                            "+1 To Teleport\n"
                            "+750-775 Defense\n"
                            "+ (0.75 Per Character Level) +0-74 To Strength (Based On Character Level)\n"
                            "Increase Maximum Life 5%\n"
                            "Damage Reduced By 8%\n"
                            "+14 Life After Each Kill\n"
                            "15% Damage Taken Goes To Mana\n"
                            "+ (1 Per Character Level) +1-99% Better Chance of Getting Magic Items (Based On Character Level)\n\n"
                            "Lvl Requirement: 65", 65);

    Runeword enlightenment("Enlightenment", "PulRalSol",
                            set<string> {"Body Armor"},
                            "5% Chance To Cast Level 15 Blaze When Struck\n"
                            "5% Chance To Cast Level 15 Fire Ball On Striking\n"
                            "+2 To Sorceress Skill Levels\n"
                            "+1 To Warmth\n"
                            "+30% Enhanced Defense\n"
                            "Fire Resist +30%\n"
                            "Damage Reduced By 7\n\n"
                            "Lvl Requirement: 45", 45);

    Runeword eternity("Eternity", "AmnBerIstSolSur",
                            set<string> {"Melee Weapons"},
                            "Indestructible\n"
                            "+260-310% Enhanced Damage\n"
                            "+9 To Minimum Damage\n"
                            "7% Life Stolen Per Hit\n"
                            "20% Chance of Crushing Blow\n"
                            "Hit Blinds Target\n"
                            "Slows Target By 33%\n"
                            "Regenerate Mana 16%\n"
                            "Replenish Life +16\n"
                            "Cannot Be Frozen\n"
                            "30% Better Chance Of Getting Magic Items\n"
                            "Level 8 Revive (88 Charges)\n\n"
                            "Lvl Requirement: 63", 63);

    Runeword exile("Exile", "VexOhmIstDol",
                            set<string> {"Shields"},
                            "ONLY WORKS ON PALADIN SHIELDS!\n\n"
                            "15% Chance To Cast Level 5 Life Tap On Striking\n"
                            "Level 13-16 Defiance Aura When Equipped\n"
                            "+2 To Offensive Auras (Paladin Only)\n"
                            "+30% Faster Block Rate\n"
                            "Freezes Target\n"
                            "+220-260% Enhanced Defense (varies)\n"
                            "Replenish Life +7\n"
                            "+5% To Maximum Cold Resist\n"
                            "+5% To Maximum Fire Resist\n"
                            "25% Better Chance Of Getting Magic Items\n"
                            "Repairs 1 Durability in 4 Seconds\n\n"
                            "Lvl Requirement: 57", 57);

    Runeword faith("Faith", "OhmJahLemEld",
                            set<string> {"Missile Weapons"},
                            "Level 12-15 Fanaticism Aura When Equipped\n"
                            "+1-2 To All Skills\n"
                            "+330% Enhanced Damage\n"
                            "Ignore Target's Defense\n"
                            "300% Bonus To Attack Rating\n"
                            "+75% Damage To Undead\n"
                            "+50 To Attack Rating Against Undead\n"
                            "+120 Fire Damage\n"
                            "All Resistances +15\n"
                            "10% Reanimate As: Returned\n"
                            "75% Extra Gold From Monsters\n\n"
                            "Lvl Requirement: 65", 65);

    Runeword famine("Famine", "FalOhmOrtJah",
                            set<string> {"Axes", "Hammers"},
                            "30% Increased Attack Speed\n"
                            "+320-370% Enhanced Damage\n"
                            "Ignore Target's Defense\n"
                            "Adds 180-200 Magic Damage\n"
                            "Adds 50-200 Fire Damage\n"
                            "Adds 51-250 Lightning Damage\n"
                            "Adds 50-200 Cold Damage\n"
                            "12% Life Stolen Per Hit\n"
                            "Prevent Monster Heal\n"
                            "+10 To Strength\n\n"
                            "Lvl Requirement: 65", 65);

    Runeword flickering_flame("Flickering Flame", "NefPulVex",
                            set<string> {"Helmets"},
                            "Level 4-8 Resist Fire Aura When Equipped (varies)\n"
                            "+3 To Fire Skills\n"
                            "-10-15% to Enemy Fire Resistance (varies)\n"
                            "+30% Enhanced Defense\n"
                            "+30 Defense vs. Missiles\n"
                            "+50-75 To Mana (varies)\n"
                            "Half Freeze Duration\n"
                            "+5% To Maximum Fire Resist\n"
                            "Poison Length Reduced by 50%\n\n"
                            "Lvl Requirement: 55", 55);

    Runeword fortitude("Fortitude", "ElSolDolLo",
                            set<string> {"Weapons", "Body Armor"},
                            "Body Armor\n"
                            "20% Chance To Cast Level 15 Chilling Armor when Struck\n"
                            "+25% Faster Cast Rate\n"
                            "+300% Enhanced Damage\n"
                            "+200% Enhanced Defense\n"
                            "+15 Defense\n"
                            "+X To Life (Based on Character Level)\n"
                            "Replenish Life +7\n"
                            "+5% To Maximum Lightning Resist\n"
                            "All Resistances +25-30\n"
                            "Damage Reduced By 7\n"
                            "12% Damage Taken Goes To Mana\n"
                            "+1 To Light Radius\n"
                            "\n"
                            "Weapon\n"
                            "20% Chance To Cast Level 15 Chilling Armor when Struck\n"
                            "+25% Faster Cast Rate\n"
                            "+300% Enhanced Damage\n"
                            "+9 To Minimum Damage\n"
                            "+50 To Attack Rating\n"
                            "20% Deadly Strike\n"
                            "Hit Causes Monster To Flee 25%\n"
                            "+200% Enhanced Defense\n"
                            "+1-1.5 To Life (Based on Character Level)\n"
                            "All Resistances +25-30\n"
                            "12% Damage Taken Goes To Mana\n"
                            "+1 To Light Radius\n\n"
                            "Lvl Requirement: 59", 59);

    Runeword fury("Fury", "JahGulEth",
                            set<string> {"Melee Weapons"},
                            "+209% Enhanced Damage\n"
                            "40% Increased Attack Speed\n"
                            "Prevent Monster Heal\n"
                            "66% Chance of Open Wounds\n"
                            "33% Chance of Deadly Strike\n"
                            "-25% Target Defense\n"
                            "20% to Attack Rating\n"
                            "6% Life Stolen Per Hit\n"
                            "Ignores Target Defense\n"
                            "+5 to Frenzy (Barbarian only)\n\n"
                            "Lvl Requirement: 65", 65);

    Runeword gloom("Gloom", "FalUmPul",
                            set<string> {"Body Armor"},
                            "15% Chance To Cast Level 3 Dim Vision When Struck\n"
                            "+10% Faster Hit Recovery\n"
                            "+200-260% Enhanced Defense\n"
                            "+10 To Strength\n"
                            "All Resistances +45\n"
                            "Half Freeze Duration\n"
                            "5% Damage Taken Goes To Mana\n"
                            "-3 To Light Radius\n\n"
                            "Lvl Requirement: 47", 47);

    Runeword grief("Grief", "EthTirLoMalRal",
                            set<string> {"Swords", "Axes"},
                            "35% Chance To Cast Level 15 Venom On Striking\n"
                            "+30-40% Increased Attack Speed\n"
                            "Damage +340-400\n"
                            "Ignore Target's Defense\n"
                            "-25% Target Defense\n"
                            "+(1.875 per character level) 1.875-185.625% Damage To Demons (Based on Character Level)\n"
                            "Adds 5-30 Fire Damage\n"
                            "-20-25% To Enemy Poison Resist\n"
                            "20% Deadly Strike\n"
                            "Prevent Monster Heal\n"
                            "+2 To Mana After Each Kill\n"
                            "+10-15 Life After Each Kill\n\n"
                            "Lvl Requirement: 59", 59);

    Runeword ground("Ground", "ShaelIoOrt",
                            set<string> {"Helmets"},
                            "+20% Faster Hit Recovery\n"
                            "+75-100% Enhanced Defense\n"
                            "+10 to Vitality\n"
                            "Increase Maximum Life 5%\n"
                            "Lightning Resist +40-60%\n"
                            "Lightning Absorb +10-15%\n\n"
                            "Lvl Requirement: 35\n"
                            "LADDER/SINGLE-PLAYER ONLY.", 35);  // todo remove after new patch

    Runeword hand_of_justice("Hand of Justice", "SurChamAmnLo",
                            set<string> {"Weapons"},
                            "100% Chance To Cast Level 36 Blaze When You Level-Up\n"
                            "100% Chance To Cast Level 48 Meteor When You Die\n"
                            "Level 16 Holy Fire Aura When Equipped\n"
                            "+33% Increased Attack Speed\n"
                            "+280-330% Enhanced Damage\n"
                            "Ignore Target's Defense\n"
                            "7% Life Stolen Per Hit\n"
                            "-20% To Enemy Fire Resist\n"
                            "20% Deadly Strike\n"
                            "Hit Blinds Target\n"
                            "Freezes Target +3\n\n"
                            "Lvl Requirement: 67", 67);

    Runeword harmony("Harmony", "TirIthSolKo",
                            set<string> {"Missile Weapons"},
                            "Level 10 Vigor Aura When Equipped\n"
                            "+200-275% Enhanced Damage\n"
                            "+9 To Minimum Damage\n"
                            "+9 To Maximum Damage\n"
                            "Adds 55-160 Lightning Damage\n"
                            "Adds 55-160 Fire Damage\n"
                            "Adds 55-160 Cold Damage\n"
                            "+2-6 To Valkyrie\n"
                            "+10 To Dexterity\n"
                            "Regenerate Mana 20%\n"
                            "+2 To Mana After Each Kill\n"
                            "+2 To Light Radius\n"
                            "Level 20 Revive (25 Charges)\n\n"
                            "Lvl Requirement: 39", 39);

    Runeword heart_of_the_oak("Heart of the Oak", "KoVexPulThul",
                            set<string> {"Staves", "Maces"},
                            "+3 To All Skills\n"
                            "+40% Faster Cast Rate\n"
                            "+75% Damage To Demons\n"
                            "+100 To Attack Rating Against Demons\n"
                            "Adds 3-14 Cold Damage for 3 seconds\n"
                            "7% Mana Stolen Per Hit\n"
                            "+10 To Dexterity\n"
                            "Replenish Life +20\n"
                            "Increase Maximum Mana 15%\n"
                            "All Resistances +30-40\n"
                            "Level 4 Oak Sage (25 Charges)\n"
                            "Level 14 Raven (60 Charges)\n\n"
                            "Lvl Requirement: 55", 55);

    Runeword hearth("Hearth", "ShaelIoThul",
                            set<string> {"Helmets"},
                            "+20% Faster Hit Recovery\n"
                            "+75-100% Enhanced Defense\n"
                            "+10 to Vitality\n"
                            "Increase Maximum Life 5%\n"
                            "Cold Resist +40-60%\n"
                            "Cold Absorb +10-15%\n"
                            "Cannot be Frozen\n\n"
                            "Lvl Requirement: 35\n"
                            "LADDER/SINGLE-PLAYER ONLY.", 35);  // todo remove after new patch

    Runeword holy_thunder("Holy Thunder", "EthRalOrtTal",
                            set<string> {"Scepters"},
                            "+60% Enhanced Damage\n"
                            "-25% Target Defense\n"
                            "5-30 Fire Damage\n"
                            "21-110 Lightning Damage\n"
                            "+75 Poison Damage for 5 seconds\n"
                            "+10 to Maximum Damage\n"
                            "+60% Lightning Resist\n"
                            "+5 to Maximum Lightning Resist\n"
                            "+3 to Holy Shock (Paladin only)\n"
                            "Level 7 Chain Lightning (60 charges)\n\n"
                            "Lvl Requirement: 23", 23);

    Runeword honor("Honor", "AmnElIthTirSol",
                            set<string> {"Melee Weapons"},
                            "+160% Enhanced Damage\n"
                            "+9 to Minimum Damage\n"
                            "+9 to Maximum Damage\n"
                            "25% Deadly Strike\n"
                            "+250 to Attack Rating\n"
                            "+1 to All Skills\n"
                            "7% Life Stolen per Hit\n"
                            "+10 Replenish Life\n"
                            "+10 to Strength\n"
                            "+1 to Light Radius\n"
                            "+2 to Mana per Kill\n\n"
                            "Lvl Requirement: 27", 27);

    Runeword hysteria("Hysteria", "ShaelKoEld",
                            set<string> {"Body Armor"},
                            "Body Armor\n"
                            "+65% Faster Run/Walk\n"
                            "+40% Increased Attack Speed\n"
                            "+20% Faster Hit Recovery\n"
                            "+6 to Evade\n"
                            "+10 to Dexterity\n"
                            "50% Slower Stamina Drain\n"
                            "All Resistances +10\n\n"
                            "Lvl Requirement: 39\n"
                            "LADDER/SINGLE-PLAYER ONLY.", 39);  // todo maybe remove after some new patch

    Runeword ice("Ice", "AmnShaelJahLo",
                            set<string> {"Missile Weapons"},
                            "100% Chance To Cast Level 40 Blizzard When You Level-up\n"
                            "25% Chance To Cast Level 22 Frost Nova On Striking\n"
                            "Level 18 Holy Freeze Aura When Equipped\n"
                            "+20% Increased Attack Speed\n"
                            "+140-210% Enhanced Damage\n"
                            "Ignore Target's Defense\n"
                            "+25-30% To Cold Skill Damage\n"
                            "-20% To Enemy Cold Resist\n"
                            "7% Life Stolen Per Hit\n"
                            "20% Deadly Strike\n"
                            "3-309% Extra Gold From Monsters (Based on Character Level)\n\n"
                            "Lvl Requirement: 65", 65);

    Runeword infinity("Infinity", "BerMalBerIst",
                            set<string> {"Polearms", "Spears"},
                            "50% Chance To Cast Level 20 Chain Lightning When You Kill An Enemy\n"
                            "Level 12 Conviction Aura When Equipped\n"
                            "+35% Faster Run/Walk\n"
                            "+255-325% Enhanced Damage\n"
                            "-(45-55)% To Enemy Lightning Resist\n"
                            "40% Chance of Crushing Blow\n"
                            "Prevent Monster Heal\n"
                            "0.5-49.5 To Vitality (Based on Character Level)\n"
                            "30% Better Chance of Getting Magic Items\n"
                            "Level 21 Cyclone Armor (30 Charges)\n\n"
                            "Lvl Requirement: 63", 63);

    Runeword insight("Insight", "RalTirTalSol",
                            set<string> {"Polearms", "Staves", "Missile Weapons"},
                            "Level 12-17 Meditation Aura When Equipped\n"
                            "+35% Faster Cast Rate\n"
                            "+200-260% Enhanced Damage (varies)\n"
                            "+9 To Minimum Damage\n"
                            "180-250% Bonus to Attack Rating\n"
                            "Adds 5-30 Fire Damage\n"
                            "+75 Poison Damage Over 5 Seconds\n"
                            "+1-6 To Critical Strike\n"
                            "+5 To All Attributes\n"
                            "+2 To Mana After Each Kill\n"
                            "23% Better Chance of Getting Magic Items\n\n"
                            "Lvl Requirement: 27", 27);

    Runeword kings_grace("King's Grace", "AmnRalThul",
                            set<string> {"Swords", "Scepters"},
                            "+100% Enhanced Damage\n"
                            "+100% Damage against Demons\n"
                            "+50% Damage against Undead\n"
                            "Adds 5-30 Fire Damage\n"
                            "Adds 3-14 Cold Damage for 3 seconds\n"
                            "+150 to Attack Rating\n"
                            "+100 to Attack Rating against Demons\n"
                            "+100 to Attack Rating against Undead\n"
                            "7% Life Stolen per hit\n\n"
                            "Lvl Requirement: 25", 25);

    Runeword kingslayer("Kingslayer", "MalUmGulFal",
                            set<string> {"Swords", "Axes"},
                            "+30% Increased Attack Speed\n"
                            "+230-270% Enhanced Damage\n"
                            "-25% Target Defense\n"
                            "20% Bonus To Attack Rating\n"
                            "33% Chance of Crushing Blow\n"
                            "50% Chance of Open Wounds\n"
                            "+1 To Vengeance\n"
                            "Prevent Monster Heal\n"
                            "+10 To Strength\n"
                            "40% Extra Gold From Monsters\n\n"
                            "Lvl Requirement: 53", 53);

    Runeword last_wish("Last Wish", "JahMalJahSurJahBer",
                            set<string> {"Axes", "Hammers", "Swords"},
                            "6% Chance To Cast Level 11 Fade When Struck\n"
                            "10% Chance To Cast Level 18 Life Tap On Striking\n"
                            "20% Chance To Cast Level 20 Charged Bolt On Attack\n"
                            "Level 17 Might Aura When Equipped\n"
                            "+330-375% Enhanced Damage\n"
                            "Ignore Target's Defense\n"
                            "60-70% Chance of Crushing Blow\n"
                            "Prevent Monster Heal\n"
                            "Hit Blinds Target\n"
                            "+(0.5 per character level) 0.5-49.5% Chance of Getting Magic Items (Based on Character Level)\n\n"
                            "Lvl Requirement: 65", 65);

    Runeword lawbringer("Lawbringer", "AmnLemKo",
                            set<string> {"Hammers", "Scepters", "Swords"},
                            "20% Chance To Cast Level 15 Decrepify on Striking\n"
                            "Level 16-18 Sanctuary Aura When Equipped (varies)\n"
                            "-50% Target Defense\n"
                            "Adds 150-210 Fire Damage\n"
                            "Adds 130-180 Cold Damage\n"
                            "7% Life Stolen Per Hit\n"
                            "Slain Monsters Rest in Peace\n"
                            "+200-250 Defense vs. Missiles\n"
                            "+10 To Dexterity\n"
                            "75% Extra Gold From Monsters\n\n"
                            "Lvl Requirement: 43", 43);

    Runeword leaf("Leaf", "TirRal",
                            set<string> {"Staves"},
                            "Adds 5-30 Fire Damage\n"
                            "+3 To Fire Skills\n"
                            "+3 To Fire Bolt (Sorceress Only)\n"
                            "+3 To Inferno (Sorceress Only)\n"
                            "+3 To Warmth (Sorceress Only)\n"
                            "+2 To Mana After Each Kill\n"
                            "+(2 Per Character Level) +2-198 To Defense (Based On Character Level)\n"
                            "Cold Resist +33%\n\n"
                            "Lvl Requirement: 19", 19);

    Runeword lionheart("Lionheart", "HelLumFal",
                            set<string> {"Body Armor"},
                            "+20% Enhanced Damage\n"
                            "Requirements -15%\n"
                            "+25 To Strength\n"
                            "+10 To Energy\n"
                            "+20 To Vitality\n"
                            "+15 To Dexterity\n"
                            "+50 To Life\n"
                            "All Resistances +30\n\n"
                            "Lvl Requirement: 41", 41);

    Runeword lore("Lore", "OrtSol",
                            set<string> {"Helmets"},
                            "+1 To All Skill Levels\n"
                            "+10 To Energy\n"
                            "+2 To Mana After Each Kill\n"
                            "Lightning Resist +30%\n"
                            "Damage Reduced By 7\n"
                            "+2 To Light Radius\n\n"
                            "Lvl Requirement: 27", 27);

    Runeword malice("Malice", "IthElEth",
                            set<string> {"Melee Weapons"},
                            "+33% Enhanced Damage\n"
                            "+9 To Maximum Damage\n"
                            "100% Chance Of Open Wounds\n"
                            "-25% Target Defense\n"
                            "-100 To Monster Defense per Hit\n"
                            "Prevent Monster Heal\n"
                            "+50 To Attack Rating\n"
                            "Drain Life -5\n\n"
                            "Lvl Requirement: 15", 15);

    Runeword mania("Mania", "ShaelKoEld",
                            set<string> {"Axes", "Claws", "Clubs", "Hammers", "Maces", "Scepters", "Staves", "Swords", "Wands"},
                            "Weapons\n"
                            "5% Chance To Cast Level 1 Burst Of Speed On Striking\n"
                            "Level 1 Fanaticism Aura When Equipped\n"
                            "+30% Increased Attack Speed\n"
                            "+180-200% Enhanced Damage\n"
                            "+75% Damage To Undead\n"
                            "+50 To Attack Rating Against Undead\n" 
                            "+10 To Dexterity\n\n"
                            "Lvl Requirement: 39\n"
                            "LADDER/SINGLE-PLAYER ONLY.", 39);  // todo maybe remove after some new patch


    Runeword melody("Melody", "ShaelKoNef",
                            set<string> {"Missile Weapons"},
                            "+50% Enhanced Damage\n"
                            "+300% Damage To Undead\n"
                            "+3 To Bow and Crossbow Skills (Amazon Only)\n"
                            "+3 To Critical Strike (Amazon Only)\n"
                            "+3 To Dodge (Amazon Only)\n"
                            "+3 To Slow Missiles (Amazon Only)\n"
                            "20% Increased Attack Speed\n"
                            "+10 To Dexterity\n"
                            "Knockback\n\n"
                            "Lvl Requirement: 39", 39);

    Runeword memory("Memory", "LumIoSolEth",
                            set<string> {"Staves"},
                            "+3 to Sorceress Skill Levels\n"
                            "33% Faster Cast Rate\n"
                            "Increase Maximum Mana 20%\n"
                            "+3 Energy Shield (Sorceress Only)\n"
                            "+2 Static Field (Sorceress Only)\n"
                            "+10 To Energy\n"
                            "+10 To Vitality\n"
                            "+9 To Minimum Damage\n"
                            "-25% Target Defense\n"
                            "Magic Damage Reduced By 7\n"
                            "+50% Enhanced Defense\n\n"
                            "Lvl Requirement: 37", 37);

    Runeword metamorphosis("Metamorphosis", "IoChamFal",
                            set<string> {"Helmets"},
                            "Werewolf strikes grant Mark for 180 seconds\n\n"
                            "Mark of the Wolf:\n"
                            "+30% Bonus to Attack Rating\n"
                            "Increase Maximum Life 40%\n"
                            "Werebear strikes grant Mark for 180 seconds\n\n"
                            "Mark of the Bear:\n"
                            "+25% Attack Speed\n"
                            "Physical Damage Received Reduced by 20%\n"
                            "+5 to Shape Shifting Skills (Druid only)\n"
                            "+25% Chance of Crushing Blow (No longer attached to Mark of the Bear)\n"
                            "+50-80% Enhanced Defense\n"
                            "+10 to Strength\n"
                            "+10 to Vitality\n"
                            "All Resistances +10\n"
                            "Cannot be Frozen\n\n"
                            "Lvl Requirement: 67\n"
                            "LADDER/SINGLE-PLAYER ONLY.", 67);  // todo remove after new patch

    Runeword mist("Mist", "ChamShaelGulThulIth",
                            set<string> {"Missile Weapons"},
                            "Level 8-12 Concentration Aura When Equipped (varies)\n"
                            "+3 To All Skills\n"
                            "20% Increased Attack Speed\n"
                            "+100% Piercing Attack\n"
                            "+325-375% Enhanced Damage (varies)\n"
                            "+9 To Maximum Damage\n"
                            "20% Bonus to Attack Rating\n"
                            "Adds 3-14 Cold Damage\n"
                            "Freeze Target +3\n"
                            "+24 Vitality\n"
                            "All Resistances +40\n\n"
                            "Lvl Requirement: 41", 41);

    Runeword mosaic("Mosaic", "MalGulAmn",
                            set<string> {"Claws"},
                            "+50% chance for finishing moves to not consume charges (Refreshes expiration timer)\n"
                            "+2 to Martial Arts (Assassin only)\n"
                            "+20% Increased Attack Speed\n"
                            "+200-250% Enhanced Damage\n"
                            "+20% Bonus to Attack Rating\n"
                            "+7% Life Steal\n"
                            "+8-15% to Cold Skill Damage\n"
                            "+8-15% to Lightning Skill Damage\n"
                            "+8-15% to Fire Skill Damage\n"
                            "Prevent Monster Heal\n\n"
                            "Lvl Requirement: 53\n"
                            "NON-LADDER/SINGLE-PLAYER ONLY.", 53);

    Runeword myth("Myth", "HelAmnNef",
                            set<string> {"Body Armor"},
                            "3% Chance To Cast Level 1 Howl When Struck\n"
                            "10% Chance To Cast Level 1 Taunt On Striking\n"
                            "+2 To Barbarian Skill Levels\n"
                            "+30 Defense vs. Missiles\n"
                            "Replenish Life +10\n"
                            "Attacker Takes Damage of 14\n"
                            "Requirements -15%\n\n"
                            "Lvl Requirement: 25", 25);

    Runeword nadir("Nadir", "NefTir",
                            set<string> {"Helmets"},
                            "+50% Enhanced Defense\n"
                            "+10 Defense\n"
                            "+30 Defense vs. Missiles\n"
                            "Level 13 Cloak of Shadows (9 Charges)\n"
                            "+2 To Mana After Each Kill\n"
                            "+5 To Strength\n"
                            "-33% Extra Gold From Monsters\n"
                            "-3 To Light Radius\n\n"
                            "Lvl Requirement: 13", 13);

    Runeword oath("Oath", "ShaelPulMalLum",
                            set<string> {"Axes", "Maces", "Swords"},
                            "30% Chance To Cast Level 20 Bone Spirit On Striking\n"
                            "Indestructible\n"
                            "+50% Increased Attack Speed\n"
                            "+210-340% Enhanced Damage\n"
                            "+75% Damage To Demons\n"
                            "+100 To Attack Rating Against Demons\n"
                            "Prevent Monster Heal\n"
                            "+10 To Energy\n"
                            "+10-15 Magic Absorb\n"
                            "Level 16 Heart of Wolverine (20 Charges)\n"
                            "Level 17 Iron Golem (14 Charges)\n\n"
                            "Lvl Requirement: 59", 59);

    Runeword obedience("Obedience", "HelKoThulEthFal",
                            set<string> {"Polearms", "Spears"},
                            "30% Chance To Cast Level 21 Enchant When You Kill An Enemy\n"
                            "40% Faster Hit Recovery\n"
                            "+370% Enhanced Damage\n"
                            "-25% Target Defense\n"
                            "Adds 3-14 Cold Damage for 3 seconds\n"
                            "-25% To Enemy Fire Resist\n"
                            "40% Chance of Crushing Blow\n"
                            "+200-300 Defense\n"
                            "+10 To Strength\n"
                            "+10 To Dexterity\n"
                            "All Resistances +20-30\n"
                            "Requirements -20%\n\n"
                            "Lvl Requirement: 41", 41);

    Runeword obsession("Obsession", "ZodIstLemLumIoNef",
                            set<string> {"Staves"},
                            "Indestructible\n"
                            "24% Chance To Cast Level 10 Weaken When Struck\n"
                            "+4 To All Skills\n"
                            "+65% Faster Cast Rate\n"
                            "+60% Faster Hit Recovery\n"
                            "Knockback\n"
                            "+10 To Vitality\n"
                            "+10 To Energy\n"
                            "Increase Maximum Life 15-25% (varies)\n"
                            "Regenerate Mana 15-30% (varies)\n"
                            "All Resistances +60-70 (varies)\n"
                            "75% Extra Gold from Monsters\n"
                            "30% Better Chance of Getting Magic Items\n\n"
                            "Lvl Requirement: 69", 69);

    Runeword passion("Passion", "DolOrtEldLem",
                            set<string> {"Weapons"},
                            "+25% Increased Attack Speed\n"
                            "+160-210% Enhanced Damage\n"
                            "50-80% Bonus To Attack Rating\n"
                            "+75% Damage To Undead\n"
                            "+50 To Attack Rating Against Undead\n"
                            "Adds 1-50 Lightning Damage\n"
                            "+1 To Berserk\n"
                            "+1 To Zeal\n"
                            "Hit Blinds Target +10\n"
                            "Hit Causes Monster To Flee 25%\n"
                            "75% Extra Gold From Monsters\n"
                            "Level 3 Heart of Wolverine (12 Charges)\n\n"
                            "Lvl Requirement: 43", 43);

    Runeword pattern("Pattern", "TalOrtThul",
                            set<string> {"Claws"},
                            "+30% Faster Block Rate\n"
                            "+40-80% Enhanced Damage (varies)\n"
                            "10% Bonus to Attack Rating\n"
                            "Adds 17-62 Fire Damage\n"
                            "Adds 1-50 Lightning Damage\n"
                            "Adds 3-14 Cold Damage\n"
                            "+75 Poison Damage Over 5 Seconds\n"
                            "+6 to Strength\n"
                            "+6 to Dexterity\n"
                            "All Resistances +15\n\n"
                            "Lvl Requirement: 23", 23);

    Runeword peace("Peace", "ShaelThulAmn",
                            set<string> {"Body Armor"},
                            "4% Chance To Cast Level 5 Slow Missiles When Struck\n"
                            "2% Chance To Cast level 15 Valkyrie On Striking\n"
                            "+2 To Amazon Skill Levels\n"
                            "+20% Faster Hit Recovery\n"
                            "+2 To Critical Strike\n"
                            "Cold Resist +30%\n"
                            "Attacker Takes Damage of 14\n\n"
                            "Lvl Requirement: 29", 29);

    Runeword phoenix("Phoenix", "VexVexLoJah",
                            set<string> {"Weapons", "Shields"},
                            "Weapon\n"
                            "100% Chance To Cast level 40 Blaze When You Level-up\n"
                            "40% Chance To Cast Level 22 Firestorm On Striking\n"
                            "Level 10-15 Redemption Aura When Equipped\n"
                            "+350-400% Enhanced Damage\n"
                            "Ignores Target's Defense\n"
                            "14% Mana Stolen Per Hit\n"
                            "-28% To Enemy Fire Resist\n"
                            "20% Deadly Strike\n"
                            "+350-400 Defense vs. Missiles\n"
                            "+15-21 Fire Absorb\n"
                            "\n"
                            "Shield\n"
                            "100% Chance To Cast level 40 Blaze When You Level-up\n"
                            "40% Chance To Cast Level 22 Firestorm On Striking\n"
                            "Level 10-15 Redemption Aura When Equipped\n"
                            "+350-400 Defense vs. Missiles\n"
                            "+350-400% Enhanced Damage\n"
                            "-28% To Enemy Fire Resist\n"
                            "+50 To Life\n"
                            "+5% To Maximum Lightning Resist\n"
                            "+10% To Maximum Fire Resist\n"
                            "+15-21 Fire Absorb\n\n"
                            "Lvl Requirement: 65", 65);

    Runeword plague("Plague", "ChamShaelUm",
                            set<string> {"Swords"},
                            "20% Chance To Cast Level 12 Lower Resist When Struck\n"
                            "25% Chance To Cast Level 15 Poison Nova On Striking\n"
                            "Level 13-17 Cleansing Aura When Equipped (varies)\n"
                            "+(1-2) All Skills\n"
                            "+20% Increased Attack Speed\n"
                            "+220-320% Enhanced Damage (varies)\n"
                            "-23% To Enemy Poison Resistance\n"
                            "+(0-29.7%) Deadly Strike (Based on Character Level)\n"
                            "+25% Chance of Open Wounds\n"
                            "Freezes Target +3\n\n"
                            "Lvl Requirement: 67", 67);

    Runeword pride("Pride", "ChamSurIoLo",
                            set<string> {"Polearms", "Spears"},
                            "25% Chance To Cast Level 17 Fire Wall When Struck\n"
                            "Level 16-20 Concentration Aura When Equipped\n"
                            "260-300% Bonus To Attack Rating\n"
                            "+1-99% Damage To Demons (Based on Character Level)\n"
                            "Adds 50-280 Lightning Damage\n"
                            "20% Deadly Strike\n"
                            "Hit Blinds Target\n"
                            "Freezes Target +3\n"
                            "+10 To Vitality\n"
                            "Replenish Life +8\n"
                            "2-186% Extra Gold From Monsters (Based on Character Level)\n\n"
                            "Lvl Requirement: 67", 67);

    Runeword principle("Principle", "RalGulEld",
                            set<string> {"Body Armor"},
                            "100% Chance To Cast Level 5 Holy Bolt On Striking\n"
                            "+2 To Paladin Skill Levels\n"
                            "+50% Damage to Undead\n"
                            "+100-150 To Life (varies)\n"
                            "15% Slower Stamina Drain\n"
                            "+5% To Maximum Poison Resist\n"
                            "Fire Resist +30%\n\n"
                            "Lvl Requirement: 55", 55);

    Runeword prudence("Prudence", "MalTir",
                            set<string> {"Body Armor"},
                            "+25% Faster Hit Recovery\n"
                            "+140-170% Enhanced Defense\n"
                            "All Resistances +25-35\n"
                            "Damage Reduced by 3\n"
                            "Magic Damage Reduced by 17\n"
                            "+2 To Mana After Each Kill\n"
                            "+1 To Light Radius\n"
                            "Repairs Durability 1 In 4 Seconds\n\n"
                            "Lvl Requirement: 49", 49);

    Runeword radiance("Radiance", "NefSolIth",
                            set<string> {"Helmets"},
                            "+75% Enhanced Defense\n"
                            "+30 Defense vs. Missiles\n"
                            "+10 To Energy\n"
                            "+10 To Vitality\n"
                            "15% Damage Goes To Mana\n"
                            "Magic Damage Reduced by 3\n"
                            "+33 To Mana\n"
                            "Damage Reduced By 7\n"
                            "+5 To Light Radius\n\n"
                            "Lvl Requirement: 27", 27);

    Runeword rain("Rain", "OrtMalIth",
                            set<string> {"Body Armor"},
                            "5% Chance To Cast Level 15 Cyclone Armor When Struck\n"
                            "5% Chance To Cast Level 15 Twister On Striking\n"
                            "+2 To Druid Skills\n"
                            "+100-150 To Mana\n"
                            "Lightning Resist +30%\n"
                            "Magic Damage Reduced By 7\n"
                            "15% Damage Taken Goes to Mana\n\n"
                            "Lvl Requirement: 49", 49);

    Runeword rhyme("Rhyme", "ShaelEth",
                            set<string> {"Shields", "Shrunken Heads", "Grimoires"},
                            "20% Increased Chance of Blocking\n"
                            "40% Faster Block Rate\n"
                            "+25 to All Resistances\n"
                            "Regenerate Mana 15%\n"
                            "Cannot Be Frozen\n"
                            "50% Extra Gold From Monsters\n"
                            "25% Better Chance Of Getting Magic Items\n\n"
                            "Lvl Requirement: 29", 29);

    Runeword rift("Rift", "HelKoLemGul",
                            set<string> {"Polearms", "Scepters"},
                            "20% Chance To Cast Level 16 Tornado On Striking\n"
                            "16% Chance To Cast Level 21 Frozen Orb On Attack\n"
                            "20% Bonus To Attack Rating\n"
                            "Adds 160-250 Magic Damage\n"
                            "Adds 60-180 Fire Damage\n"
                            "+5-10 To All Stats (varies)\n"
                            "+10 To Dexterity\n"
                            "38% Damage Taken Goes To Mana\n"
                            "75% Extra Gold From Monsters\n"
                            "Level 15 Iron Maiden (40 Charges)\n"
                            "Requirements -20%\n\n"
                            "Lvl Requirement: 53", 53);

    Runeword ritual("Ritual", "AmnShaelOhm",
                            set<string> {"Daggers"},
                            "13% Chance To Cast Level 1 Sigil Death When Struck\n"
                            "+20% Increased Attack Speed\n"
                            "+200-270% Enhanced Damage\n"
                            "+150-250% Damage To Demons\n"
                            "+200-260% Bonus To Attack Rating\n"
                            "+3-5 Life After Each Kill\n"
                            "Slain Monsters Rest In Peace\n"
                            "7% Life Stolen Per Hit\n"
                            "+20% Increased Attack Speed\n"
                            "+50% Enhanced Damage\n\n"
                            "Lvl Requirement: 57", 57);

    Runeword sanctuary("Sanctuary", "KoKoMal",
                            set<string> {"Shields"},
                            "+20% Faster Hit Recovery\n"
                            "+20% Faster Block Rate\n"
                            "20% Increased Chance of Blocking\n"
                            "+130-160% Enhanced Defense\n"
                            "+250 Defense vs. Missiles\n"
                            "+20 To Dexterity\n"
                            "All Resistances +50-70\n"
                            "Magic Damage Reduced by 7\n"
                            "Level 12 Slow Missiles (60 Charges)\n\n"
                            "Lvl Requirement: 49", 49);

    Runeword silence("Silence", "DolEldHelIstTirVex",
                            set<string> {"Weapons"},
                            "200% Enhanced Damage\n"
                            "+75% Damage To Undead\n"
                            "Requirements -20%\n"
                            "20% Increased Attack Speed\n"
                            "+50 To Attack Rating Against Undead\n"
                            "+2 To All Skills\n"
                            "All Resistances +75\n"
                            "20% Faster Hit Recovery\n"
                            "11% Mana Stolen Per Hit\n"
                            "Hit Causes Monster To Flee 25%\n"
                            "Hit Blinds Target +33\n"
                            "+2 To Mana After Each Kill\n"
                            "30% Better Chance Of Getting Magic Items\n\n"
                            "Lvl Requirement: 55", 55);

    Runeword smoke("Smoke", "NefLum",
                            set<string> {"Body Armor"},
                            "+75% Enhanced Defense\n"
                            "+280 Defense vs. Missiles\n"
                            "All Resistances +50\n"
                            "20% Faster Hit Recovery\n"
                            "Level 6 Weaken (18 Charges)\n"
                            "+10 To Energy\n"
                            "-1 To Light Radius\n\n"
                            "Lvl Requirement: 37", 37);

    Runeword spirit("Spirit", "TalThulOrtAmn",
                            set<string> {"Shields", "Swords"},
                            "+2 To All Skills\n"
                            "+25-35% Faster Cast Rate (varies)\n"
                            "+55% Faster Hit Recovery\n"
                            "+250 Defense vs. Missiles\n"
                            "+22 To Vitality\n"
                            "+89-112 To Mana (varies)\n"
                            "\n"
                            "Swords only:\n"
                            "+75 Poison Damage Over 5 Seconds\n"
                            "Adds 3-14 Cold Damage For 3 Seconds\n"
                            "Adds 1-50 Lightning Damage\n"
                            "Adds 1-50 Lightning Damage\n"
                            "\n"
                            "Shields only:\n"
                            "Poison Resist +35%\n"
                            "Cold Resist +35%\n"
                            "Lightning Resist +35%\n"
                            "Attacker Takes Damage of 14\n\n"
                            "Lvl Requirement: 25", 25);

    Runeword splendor("Splendor", "EthLum",
                            set<string> {"Shields", "Shrunken Heads", "Grimoires"},
                            "+1 To All Skills\n"
                            "+10% Faster Cast Rate\n"
                            "+20% Faster Block Rate\n"
                            "+60-100% Enhanced Defense\n"
                            "+10 To Energy\n"
                            "Regenerate Mana 15%\n"
                            "50% Extra Gold From Monsters\n"
                            "20% Better Chance of Getting Magic Items\n"
                            "+3 To Light Radius\n\n"
                            "Lvl Requirement: 37", 37);

    Runeword stealth("Stealth", "TalEth",
                            set<string> {"Body Armor"},
                            "Magic Damage Reduced By 3\n"
                            "+6 To Dexterity\n"
                            "+15 To Maximum Stamina\n"
                            "Poison Resist +30%\n"
                            "Regenerate Mana 15%\n"
                            "25% Faster Run/Walk\n"
                            "25% Faster Cast Rate\n"
                            "25% Faster Hit Recovery\n\n"
                            "Lvl Requirement: 17", 17);

    Runeword steel("Steel", "TirEl",
                            set<string> {"Swords", "Axes", "Maces"},
                            "20% Enhanced Damage\n"
                            "+3 To Minimum Damage\n"
                            "+3 To Maximum Damage\n"
                            "+50 To Attack Rating\n"
                            "50% Chance Of Open Wounds\n"
                            "25% Increased Attack Speed\n"
                            "+2 To Mana After Each Kill\n"
                            "+1 To Light Radius\n\n"
                            "Lvl Requirement: 13", 13);

    Runeword stone("Stone", "ShaelUmPulLum",
                            set<string> {"Body Armor"},
                            "+60% Faster Hit Recovery\n"
                            "+250-290% Enhanced Defense\n"
                            "+300 Defense vs. Missile\n"
                            "+16 To Strength\n"
                            "+16 To Vitality\n"
                            "+10 To Energy\n"
                            "All Resistances +15\n"
                            "Level 16 Molten Boulder (80 Charges)"
                            "Level 16 Clay Golem (16 Charges)\n\n"
                            "Lvl Requirement: 47", 47);

    Runeword strength("Strength", "AmnTir",
                            set<string> {"Melee Weapons"},
                            "35% Enhanced Damage\n"
                            "25% Chance Of Crushing Blow\n"
                            "7% Life Stolen Per Hit\n"
                            "+2 To Mana After Each Kill\n"
                            "+20 To Strength\n"
                            "+10 To Vitality\n\n"
                            "Lvl Requirement: 25", 25);

    Runeword temper("Temper", "ShaelIoRal",
                            set<string> {"Helmets"},
                            "+20% Faster Hit Recovery\n"
                            "+75-100% Enhanced Defense\n"
                            "+10 to Vitality\n"
                            "Increase Maximum Life 5%\n"
                            "Fire Resist +40-60%\n"
                            "Fire Absorb +10-15%\n\n"
                            "Lvl Requirement: 35\n"
                            "LADDER/SINGLE-PLAYER ONLY.", 35);  // todo remove after new patch

    Runeword treachery("Treachery", "ShaelThulLem",
                            set<string> {"Body Armor"},
                            "5% Chance To Cast Level 15 Fade When Struck\n"
                            "25% Chance To Cast level 15 Venom On Striking\n"
                            "+2 To Assassin Skills\n"
                            "+45% Increased Attack Speed\n"
                            "+20% Faster Hit Recovery\n"
                            "Cold Resist +30%\n"
                            "50% Extra Gold From Monsters\n\n"
                            "Lvl Requirement: 43", 43);

    Runeword unbending_will("Unbending Will", "FalIoIthEldElHel",
                            set<string> {"Swords"},
                            "18% Chance To Cast Level 18 Taunt On Striking\n"
                            "+3 To Combat Skills (Barbarian Only)\n"
                            "+20-30% Increased Attack Speed (varies)\n"
                            "+300-350% Enhanced Damage (varies)\n"
                            "+9 To Maximum Damage\n"
                            "+50 To Attack Rating\n"
                            "+75% Damage to Undead\n"
                            "+50 Attack Rating Against Undead\n"
                            "8-10% Life Stolen Per Hit (varies)\n"
                            "Prevent Monster Heal\n"
                            "+10 To Strength\n"
                            "10 To Vitality\n"
                            "Damage Reduced By 8\n"
                            "+1 Light Radius\n"
                            "Requirements -20%\n\n"
                            "Lvl Requirement: 41", 41);

    Runeword venom("Venom", "TalDolMal",
                            set<string> {"Weapons"},
                            "Hit Causes Monster To Flee 25%\n"
                            "Prevent Monster Heal\n"
                            "Ignore Target's Defense\n"
                            "7% Mana Stolen Per Hit\n"
                            "Level 15 Poison Explosion (27 Charges)\n"
                            "Level 13 Poison Nova (11 Charges)\n"
                            "+273 Poison Damage Over 6 seconds\n\n"
                            "Lvl Requirement: 49", 49);

    Runeword vigilance("Vigilance", "DolGul",
                            set<string> {"Shields", "Shrunken Heads", "Grimoires"},
                            "5% Chance To Cast Level 10 Ring Of Fire When Struck\n"
                            "+10% Faster Run/Walk\n"
                            "+30% Faster Block Rate\n"
                            "+20-40 To Life\n"
                            "+20-40 To Mana\n"
                            "All Resistances +25-35\n"
                            "+75-100% Enhanced Defense\n"
                            "Replenish Life +7\n"
                            "+5% To Maximum Poison Resist\n\n"
                            "Lvl Requirement: 53", 53);

    Runeword voice_of_reason("Voice of Reason", "LemKoElEld",
                            set<string> {"Maces", "Swords"},
                            "15% Chance To Cast Level 13 Frozen Orb On Striking\n"
                            "18% Chance To Cast Level 20 Ice Blast On Striking\n"
                            "+50 To Attack Rating\n"
                            "+220-350% Damage To Demons\n"
                            "+355-375% Damage To Undead\n"
                            "+50 To Attack Rating Against Undead\n"
                            "Adds 100-220 Cold Damage\n"
                            "-24% To Enemy Cold Resistance\n"
                            "+10 To Dexterity\n"
                            "Cannot Be Frozen\n"
                            "75% Extra Gold From Monsters\n"
                            "+1 To Light Radius\n\n"
                            "Lvl Requirement: 43", 43);

    // blizzard please dont use VOID as name lmao
    Runeword void_("Void", "ThulZodIst",
                            set<string> {"Daggers"},
                            "+2 To All Skills\n"
                            "+40% Faster Cast Rate\n"
                            "+10-15% To Magic Skill Damage\n"
                            "+1 To Abyss (Level 3)\n"
                            "+8-12 To All Attributes\n"
                            "Level 4 Decrepify (35/35 Charges)\n"
                            "Adds 3-14 Cold Damage\n"
                            "Indestructible\n"
                            "30% Better Chance Of Getting Magic Items\n\n"
                            "Lvl Requirement: 69", 69);

    Runeword wealth("Wealth", "LemKoTir",
                            set<string> {"Body Armor"},
                            "300% Extra Gold From Monsters\n"
                            "100% Better Chance Of Getting Magic Items\n"
                            "+2 To Mana After Each Kill\n"
                            "+10 To Dexterity\n\n"
                            "Lvl Requirement: 43", 43);

    Runeword white("White", "DolIo",
                            set<string> {"Wands"},
                            "Hit Causes Monster To Flee 25%\n"
                            "+10 To Vitality\n"
                            "+3 To Poison and Bone Spells (Necromancer Only)\n"
                            "+3 To Bone Armor (Necromancer Only)\n"
                            "+2 To Bone Spear (Necromancer Only)\n"
                            "+4 To Skeleton Mastery (Necromancer Only)\n"
                            "Magic Damage Reduced By 4\n"
                            "20% Faster Cast Rate\n"
                            "+13 To Mana\n\n"
                            "Lvl Requirement: 35", 35);

    Runeword wind("Wind", "SurEl",
                            set<string> {"Melee Weapons"},
                            "10% Chance To Cast Level 9 Tornado On Striking\n"
                            "+20% Faster Run/Walk\n"
                            "+40% Increased Attack Speed\n"
                            "+15% Faster Hit Recovery\n"
                            "+120-160% Enhanced Damage\n"
                            "-50% Target Defense\n"
                            "+50 To Attack Rating\n"
                            "Hit Blinds Target\n"
                            "+1 To Light Radius\n"
                            "Level 13 Twister (127 Charges)\n\n"
                            "Lvl Requirement: 61", 61);

    Runeword wisdom("Wisdom", "PulIthEld",
                            set<string> {"Helmets"},
                            "+33% Piercing Attack\n"
                            "+(15-25)% Bonus to Attack Rating (varies)\n"
                            "4-8% Mana Stolen Per Hit (varies)\n"
                            "+30% Enhanced Defense\n"
                            "+10 Energy\n"
                            "15% Slower Stamina Drain\n"
                            "Cannot Be Frozen\n"
                            "+5 Mana After Each Kill\n"
                            "15% Damage Taken Goes to Mana\n\n"
                            "Lvl Requirement: 45", 45);

    Runeword wrath("Wrath", "PulLumBerMal",
                            set<string> {"Missile Weapons"},
                            "30% Chance To Cast Level 1 Decrepify On Striking\n"
                            "5% Chance To Cast Level 10 Life Tap On Striking\n"
                            "+375% Damage To Demons\n"
                            "+100 To Attack Rating Against Demons\n"
                            "+250-300% Damage To Undead\n"
                            "Adds 85-120 Magic Damage\n"
                            "Adds 41-240 Lightning Damage\n"
                            "20% Chance of Crushing Blow\n"
                            "Prevent Monster Heal\n"
                            "+10 To Energy\n"
                            "Cannot Be Frozen\n\n"
                            "Lvl Requirement: 63", 63);

    Runeword zephyr("Zephyr", "OrtEth",
                            set<string> {"Missile Weapons"},
                            "+33% Enhanced Damage\n"
                            "+66 To Attack Rating\n"
                            "Adds 1-50 Lightning Damage\n"
                            "-25% Target Defense\n"
                            "+25 Defense\n"
                            "25% Faster Run/Walk\n"
                            "25% Increased Attack Speed\n"
                            "7% Chance To Cast Level 1 Twister When Struck\n\n"
                            "Lvl Requirement: 21", 21);


    // don't forget to add new runewords here too
    temp.insert(temp.end(), {ancients_pledge, authority, beast, black, bone, bramble,
                            brand, breath_of_the_dying, bulwark, call_to_arms,
                            chains_of_honor, chaos, coven, crescent_moon, cure, death,
                            delirium, destruction, doom, dragon, dream, duress,
                            edge, enigma, enlightenment, eternity, exile, faith,
                            famine, flickering_flame, fortitude, fury, gloom,
                            grief, ground, hand_of_justice, harmony, heart_of_the_oak, hearth,
                            holy_thunder, honor, hysteria, ice, infinity, insight,
                            kings_grace, kingslayer, last_wish, lawbringer,
                            leaf, lionheart, lore, malice, mania, melody, memory, metamorphosis, mist, mosaic,
                            myth, nadir, oath, obedience, obsession, passion,
                            pattern, peace, phoenix, plague, pride, principle,
                            prudence, radiance, rain, rhyme, rift, ritual, sanctuary,
                            silence, smoke, spirit, splendor, stealth, steel,
                            stone, strength, temper, treachery, unbending_will, venom, vigilance, 
                            voice_of_reason, void_, wealth, white, wind, wisdom, wrath,
                            zephyr});

}


// calculation of runewords happens here
vector<Runeword> actual_calc(set<wxString> &user_runes, wxString user_item_wx,
                                int user_sockets, wxString levelreq){

    string user_item = user_item_wx.ToStdString();
    set<string> user_item_set = user_item_to_set(user_item);

    // extract lvl from max level req string (get last two chars which is actual lvl e.g. 47)
    int max_lvl;
    if (levelreq == wxT("Any")){
        max_lvl = 100;
    }
    else {
        string levelreq_string = levelreq.ToStdString();                        // covert wxString to string
        max_lvl = stoi(levelreq_string.substr(levelreq_string.length() - 2));   // get last 2 digits and convert them to int
    }


    vector<Runeword> results = {};

    // map items of gui selection to runeword item types

    // find all runewords that the user possible create now with this item
    for (Runeword r: runewords){
        // first filter: amount of runes required
        if (user_sockets == r.sockets){
            // second filter: item types that support this runeword
            for (string s: user_item_set){
                if ((r.items).count(s)){
                    // second last filter: check if user has all the required runes
                    if (isSubset(r.runes, user_runes)){
                        // last filter: check if lvl req is met
                        if (r.level_req <= max_lvl){
                            // user definitely can make this runeword right now
                            results.push_back(r);
                        }

                    }
                }
            }

        }

    }

    return results;
}



// is s1 a subset of s2?
bool isSubset(set<string> &s1, set<wxString> &s2){
    for (string s: s1){
        if (s2.count(wxString(s)) == 0){
            return false;
        }
    }
    return true;
}


set<string> user_item_to_set(string user_item){
    set<string> final;
    final.insert(user_item);

    // melee weapons
    if (user_item == "Axes" || user_item == "Claws"
     || user_item == "Clubs" || user_item == "Daggers"
     || user_item == "Flails" || user_item == "Hammers"
     || user_item == "Katars" || user_item == "Maces"
     || user_item == "Polearms" || user_item == "Scepters"
     || user_item == "Spears" || user_item == "Staves"
     || user_item == "Swords" || user_item == "Wands"){
        final.insert("Melee Weapons");
        final.insert("Weapons");
    }

    // missile weapons
    else if (user_item == "Bows" || user_item == "Crossbows"){
        final.insert("Missile Weapons");
        final.insert("Weapons");
    }

    // exception because javelin is subclass of subclass of subclass of weapon
    else if (user_item == "Javelins"){
        final.insert("Spears");
        final.insert("Melee Weapons");
        final.insert("Weapons");
    }

    // exception because an orb technically is neither melee nor missile type
    else if (user_item == "Orbs"){
        final.insert("Weapons");
    }

    return final;
}


// constructor
Runeword::Runeword(string s1, string s2, set<string> set1, string s3, int s4){
    name = s1;
    runeword = s2;
    items = set1;
    sockets = calculateSockets(runeword);
    runes = calculateRunes(runeword);
    runeword_stats = s3;
    level_req = s4;
}


// destructor
Runeword::~Runeword(){}
