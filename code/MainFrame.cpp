#include "MainFrame.h"
#include "Runeword.h"
#include <algorithm>
#include <wx/settings.h>
#include <wx/dialog.h>
#include <wx/sizer.h>


namespace {
wxString AlignBreakpointText(const wxString& raw_text) {
    const wxArrayString lines = wxSplit(raw_text, '\n');
    size_t max_left_width = 0;

    for (const wxString& line : lines) {
        const int tab_pos = line.Find('\t');
        if (tab_pos == wxNOT_FOUND) {
            continue;
        }

        wxString trimmed_left = line.Left(tab_pos);
        trimmed_left.Trim(true);
        trimmed_left.Trim(false);
        max_left_width = std::max(max_left_width, static_cast<size_t>(trimmed_left.length()));
    }

    wxString aligned;
    for (size_t i = 0; i < lines.size(); ++i) {
        const wxString& line = lines[i];
        const int tab_pos = line.Find('\t');
        if (tab_pos == wxNOT_FOUND) {
            aligned += line;
        } else {
            wxString left = line.Left(tab_pos);
            left.Trim(true);
            left.Trim(false);
            const wxString right = line.Mid(tab_pos + 1);

            size_t padding = 2;  // minimal gap between columns
            if (max_left_width > static_cast<size_t>(left.length())) {
                padding += max_left_width - static_cast<size_t>(left.length());
            }

            aligned += left + wxString(' ', padding) + right;
        }

        if (i + 1 < lines.size()) {
            aligned += "\n";
        }
    }

    return aligned;
}

void ShowBreakpointDialog(wxWindow* parent, const wxString& title, const wxString& raw_text) {
    wxDialog dialog(parent, wxID_ANY, title, wxDefaultPosition, wxDefaultSize,
                    wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER);

    wxBoxSizer* main_sizer = new wxBoxSizer(wxVERTICAL);
    wxTextCtrl* text = new wxTextCtrl(&dialog, wxID_ANY, AlignBreakpointText(raw_text),
                                      wxDefaultPosition, wxSize(580, 520),
                                      wxTE_MULTILINE | wxTE_READONLY | wxTE_DONTWRAP);
    text->SetFont(wxFont(11, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    main_sizer->Add(text, 1, wxEXPAND | wxALL, 10);
    main_sizer->Add(dialog.CreateSeparatedButtonSizer(wxOK), 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);

    dialog.SetSizerAndFit(main_sizer);
    dialog.SetMinSize(wxSize(520, 420));
    dialog.CentreOnParent();
    dialog.ShowModal();
}
}  // namespace


// event table (must be declared in h file and defined here)
BEGIN_EVENT_TABLE (MainFrame, wxFrame)
    EVT_BUTTON(id_btn_invert, MainFrame::InvertRunes)
    EVT_BUTTON(id_btn_reset, MainFrame::ResetRunes)
    EVT_BUTTON(id_btn_sort, MainFrame::SortRunes)
    EVT_BUTTON(id_btn_calc, MainFrame::CalculateResults)
    EVT_LISTBOX(id_runeword_listbox, MainFrame::ShowRunewordStats)
END_EVENT_TABLE()


MainFrame::MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size) :
    wxFrame(NULL, -1 , title, pos, size){
    const wxColour themed_bg = wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW);
    const wxColour themed_fg = wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT);
    SetBackgroundColour(themed_bg);
    SetForegroundColour(themed_fg);
    static_results->SetBackgroundColour(themed_bg);
    static_results->SetForegroundColour(themed_fg);

    // define custom font (enables monospace on windows)
    wxFont* my_font = new wxFont(14, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL,
        wxFONTWEIGHT_NORMAL);

    // apply custom font to runeword stats
    static_results->SetFont(*my_font);

    // panel for invert button
    wxPanel *btn_panel_invert = new wxPanel(this, wxID_ANY,
        wxPoint(20, 20), wxSize(160, 40));

    // panel for reset button
    wxPanel *btn_panel_reset = new wxPanel(this, wxID_ANY,
        wxPoint(20, 64), wxSize(160, 40));

    // panel for sort button
    wxPanel *btn_panel_sort = new wxPanel(this, wxID_ANY,
        wxPoint(20, 460), wxSize(160, 40));

    // use system colors so this works in both dark and light themes
    btn_panel_invert->SetBackgroundColour(themed_bg);
    btn_panel_reset->SetBackgroundColour(themed_bg);
    btn_panel_sort->SetBackgroundColour(themed_bg);

    // panel for calculate button
    wxPanel *btn_panel_calc = new wxPanel(this, wxID_ANY,
        wxPoint(294, 390), wxSize(200, 60));
    btn_panel_calc->SetBackgroundColour(themed_bg);

    // panel for rune checkboxes
    wxPanel *checkbox_panel = new wxPanel(this, wxID_ANY,
        wxPoint(25, 120), wxSize(184, 320));    // adjust value of first wxSize entry if names are cut off
    checkbox_panel->SetBackgroundColour(themed_bg);

    // vertical divider 1
    wxStaticLine *vertical_div_1 = new wxStaticLine(this, wxID_ANY,
        wxPoint(520, 0), wxSize(1, 440));

    // vertical divider 2
    wxStaticLine *vertical_div_2 = new wxStaticLine(this, wxID_ANY,
        wxPoint(1020, 0), wxSize(1, 440));

    // display static text (item type)
    wxStaticText *static_itemselection = new wxStaticText(this, wxID_ANY,
        "Item Type", wxPoint(294, 110), wxSize(80, 30));

    // display static text (sockets)
    wxStaticText *static_sockets = new wxStaticText(this, wxID_ANY,
        "Sockets", wxPoint(294, 210), wxSize(80, 30));

    // display static text (max level req)
    wxStaticText *static_levelreq = new wxStaticText(this, wxID_ANY,
        "Max Level Requirement", wxPoint(294, 310), wxSize(160, 30));

    // display static text (possible runewords)
    wxStaticText *static_runeword_results = new wxStaticText(this, wxID_ANY,
        "Possible runewords:", wxPoint(572, 16), wxSize(280, 20));


    choice_arr1.Add("Axes");
    choice_arr1.Add("Body Armor");
    choice_arr1.Add("Bows");        // missile weapon
    choice_arr1.Add("Claws");
    choice_arr1.Add("Clubs");
    choice_arr1.Add("Crossbows");   // missile weapon
    choice_arr1.Add("Daggers");
    choice_arr1.Add("Flails");
    choice_arr1.Add("Grimoires"); // same as Shields, Shrunken Heads or Targes
    choice_arr1.Add("Hammers");
    choice_arr1.Add("Helmets");
    choice_arr1.Add("Javelins");
    choice_arr1.Add("Katars");
    choice_arr1.Add("Maces");
    choice_arr1.Add("Orbs");        // doesnt count as missile AFAIK
    choice_arr1.Add("Polearms");
    choice_arr1.Add("Scepters");
    choice_arr1.Add("Shields"); // Targes is the same as Shields for runewords
    choice_arr1.Add("Shrunken Heads"); // technically no need to list Shrunken Heads because they are 2 sockets max and would be the same count as Shields runeword-wise. same logic for Grimoires
    choice_arr1.Add("Spears");
    choice_arr1.Add("Staves");
    choice_arr1.Add("Swords");
    choice_arr1.Add("Wands");

    // weapon choice
    choice_1 = new wxChoice(this, wxID_ANY, wxPoint(294, 140),
    wxSize(200, 30), choice_arr1);
    choice_1->SetSelection(1);

    // socket choice
    choice_arr2.Add(wxT("2"));
    choice_arr2.Add(wxT("3"));
    choice_arr2.Add(wxT("4"));
    choice_arr2.Add(wxT("5"));
    choice_arr2.Add(wxT("6"));
    choice_2 = new wxChoice(this, wxID_ANY, wxPoint(294, 240),
    wxSize(200, 30), choice_arr2);
    choice_2->SetSelection(0);

    // max level req choice (interestingly there are no runewords with lvl 31 or 33 req)
    choice_arr3.Add(wxT("Any"));
    choice_arr3.Add(wxT("<= 13"));
    choice_arr3.Add(wxT("<= 15"));
    choice_arr3.Add(wxT("<= 17"));
    choice_arr3.Add(wxT("<= 19"));
    choice_arr3.Add(wxT("<= 21"));
    choice_arr3.Add(wxT("<= 23"));
    choice_arr3.Add(wxT("<= 25"));
    choice_arr3.Add(wxT("<= 27"));
    choice_arr3.Add(wxT("<= 29"));
    choice_arr3.Add(wxT("<= 35"));
    choice_arr3.Add(wxT("<= 37"));
    choice_arr3.Add(wxT("<= 39"));
    choice_arr3.Add(wxT("<= 41"));
    choice_arr3.Add(wxT("<= 43"));
    choice_arr3.Add(wxT("<= 45"));
    choice_arr3.Add(wxT("<= 47"));
    choice_arr3.Add(wxT("<= 49"));
    choice_arr3.Add(wxT("<= 51"));
    choice_arr3.Add(wxT("<= 53"));
    choice_arr3.Add(wxT("<= 55"));
    choice_arr3.Add(wxT("<= 57"));
    choice_arr3.Add(wxT("<= 59"));
    choice_arr3.Add(wxT("<= 61"));
    choice_arr3.Add(wxT("<= 63"));
    choice_arr3.Add(wxT("<= 65"));
    choice_arr3.Add(wxT("<= 67"));
    choice_arr3.Add(wxT("<= 69"));

    choice_3 = new wxChoice(this, wxID_ANY, wxPoint(294, 340),
    wxSize(200, 30), choice_arr3);
    choice_3->SetSelection(0);

    // widget: menubar tabs
    wxMenuBar *menuBar = new wxMenuBar;


    // LIST RUNEWORDS MENU
    wxMenu* menuRunewordList = new wxMenu();
    menuBar->Append(menuRunewordList, "&List Runewords");

    // A-C
    wxMenu* menuAC = new wxMenu();
    menuRunewordList->Append(wxID_ANY, "&A-C", menuAC);
    menuAC->Append(id_runewordlist_ancients_pledge, "&Ancient's Pledge");
    menuAC->Append(id_runewordlist_authority, "&Authority");
    menuAC->Append(id_runewordlist_beast, "&Beast");
    menuAC->Append(id_runewordlist_black, "&Black");
    menuAC->Append(id_runewordlist_bone, "&Bone");
    menuAC->Append(id_runewordlist_bramble, "&Bramble");
    menuAC->Append(id_runewordlist_brand, "&Brand");
    menuAC->Append(id_runewordlist_breath_of_the_dying, "&Breath of the Dying");
    menuAC->Append(id_runewordlist_bulwark, "&Bulwark");
    menuAC->Append(id_runewordlist_call_to_arms, "&Call to Arms");
    menuAC->Append(id_runewordlist_chains_of_honor, "&Chains of Honor");
    menuAC->Append(id_runewordlist_coven, "&Coven");
    menuAC->Append(id_runewordlist_crescent_moon, "&Crescent Moon");
    menuAC->Append(id_runewordlist_cure, "&Cure");

    // D-E
    wxMenu* menuDE = new wxMenu();
    menuRunewordList->Append(wxID_ANY, "&D-E", menuDE);
    menuDE->Append(id_runewordlist_death, "&Death");
    menuDE->Append(id_runewordlist_delirium, "&Delirium");
    menuDE->Append(id_runewordlist_destruction, "&Destruction");
    menuDE->Append(id_runewordlist_doom, "&Doom");
    menuDE->Append(id_runewordlist_dragon, "&Dragon");
    menuDE->Append(id_runewordlist_dream, "&Dream");
    menuDE->Append(id_runewordlist_duress, "&Duress");
    menuDE->Append(id_runewordlist_edge, "&Edge");
    menuDE->Append(id_runewordlist_enigma, "&Enigma");
    menuDE->Append(id_runewordlist_enlightenment, "&Enlightenment");
    menuDE->Append(id_runewordlist_eternity, "&Eternity");
    menuDE->Append(id_runewordlist_exile, "&Exile");

    // F-H
    wxMenu* menuFH = new wxMenu();
    menuRunewordList->Append(wxID_ANY, "&F-H", menuFH);
    menuFH->Append(id_runewordlist_faith, "&Faith");
    menuFH->Append(id_runewordlist_famine, "&Famine");
    menuFH->Append(id_runewordlist_flickering_flame, "&Flickering Flame");
    menuFH->Append(id_runewordlist_fortitude, "&Fortitude");
    menuFH->Append(id_runewordlist_fury, "&Fury");
    menuFH->Append(id_runewordlist_gloom, "&Gloom");
    menuFH->Append(id_runewordlist_grief, "&Grief");
    menuFH->Append(id_runewordlist_ground, "&Ground");
    menuFH->Append(id_runewordlist_hand_of_justice, "&Hand of Justice");
    menuFH->Append(id_runewordlist_harmony, "&Harmony");
    menuFH->Append(id_runewordlist_heart_of_the_oak, "&Heart of the Oak");
    menuFH->Append(id_runewordlist_hearth, "&Hearth");
    menuFH->Append(id_runewordlist_holy_hunder, "&Holy Thunder");
    menuFH->Append(id_runewordlist_honor, "&Honor");
    menuFH->Append(id_runewordlist_hysteria, "&Hysteria");

    // I-L
    wxMenu* menuIL = new wxMenu();
    menuRunewordList->Append(wxID_ANY, "&I-L", menuIL);
    menuIL->Append(id_runewordlist_ice, "&Ice");
    menuIL->Append(id_runewordlist_infinity, "&Infinity");
    menuIL->Append(id_runewordlist_insight, "&Insight");
    menuIL->Append(id_runewordlist_kings_grace, "&King's Grace");
    menuIL->Append(id_runewordlist_kingslayer, "&Kingslayer");
    menuIL->Append(id_runewordlist_last_wish, "&Last Wish");
    menuIL->Append(id_runewordlist_lawbringer, "&Lawbringer");
    menuIL->Append(id_runewordlist_leaf, "&Leaf");
    menuIL->Append(id_runewordlist_lionheart, "&Lionheart");
    menuIL->Append(id_runewordlist_lore, "&Lore");

    // M-O
    wxMenu* menuMO = new wxMenu();
    menuRunewordList->Append(wxID_ANY, "&M-O", menuMO);
    menuMO->Append(id_runewordlist_malice, "&Malice");
    menuMO->Append(id_runewordlist_mania, "&Mania");
    menuMO->Append(id_runewordlist_melody, "&Melody");
    menuMO->Append(id_runewordlist_memory, "&Memory");
    menuMO->Append(id_runewordlist_metamorphosis, "&Metamorphosis");
    menuMO->Append(id_runewordlist_mist, "&Mist");
    menuMO->Append(id_runewordlist_mosaic, "&Mosaic");
    menuMO->Append(id_runewordlist_myth, "&Myth");
    menuMO->Append(id_runewordlist_nadir, "&Nadir");
    menuMO->Append(id_runewordlist_oath, "&Oath");
    menuMO->Append(id_runewordlist_obedience, "&Obedience");
    menuMO->Append(id_runewordlist_obsession, "&Obesession");

    // P-R
    wxMenu* menuPR = new wxMenu();
    menuRunewordList->Append(wxID_ANY, "&P-R", menuPR);
    menuPR->Append(id_runewordlist_passion, "&Passion");
    menuPR->Append(id_runewordlist_pattern, "&Pattern");
    menuPR->Append(id_runewordlist_peace, "&Peace");
    menuPR->Append(id_runewordlist_phoenix, "&Phoenix");
    menuPR->Append(id_runewordlist_plague, "&Plague");
    menuPR->Append(id_runewordlist_pride, "&Pride");
    menuPR->Append(id_runewordlist_principle, "&Principle");
    menuPR->Append(id_runewordlist_prudence, "&Prudence");
    menuPR->Append(id_runewordlist_radiance, "&Radiance");
    menuPR->Append(id_runewordlist_rain, "&Rain");
    menuPR->Append(id_runewordlist_rhyme, "&Rhyme");
    menuPR->Append(id_runewordlist_rift, "&Rift");
    menuPR->Append(id_runewordlist_ritual, "&Ritual");

    // S-T
    wxMenu* menuST = new wxMenu();
    menuRunewordList->Append(wxID_ANY, "&S-T", menuST);
    menuST->Append(id_runewordlist_sanctuary, "&Sanctuary");
    menuST->Append(id_runewordlist_silence, "&Silence");
    menuST->Append(id_runewordlist_smoke, "&Smoke");
    menuST->Append(id_runewordlist_spirit, "&Spirit");
    menuST->Append(id_runewordlist_splendor, "&Splendor");
    menuST->Append(id_runewordlist_stealth, "&Stealth");
    menuST->Append(id_runewordlist_steel, "&Steel");
    menuST->Append(id_runewordlist_stone, "&Stone");
    menuST->Append(id_runewordlist_strength, "&Strength");
    menuST->Append(id_runewordlist_temper, "&Temper");
    menuST->Append(id_runewordlist_treachery, "&Treachery");

    // U-Z
    wxMenu* menuUZ = new wxMenu();
    menuRunewordList->Append(wxID_ANY, "&U-Z", menuUZ);
    menuUZ->Append(id_runewordlist_unbending_will, "&Unbending Will");
    menuUZ->Append(id_runewordlist_venom, "&Venom");
    menuUZ->Append(id_runewordlist_vigilance, "&Vigilance");
    menuUZ->Append(id_runewordlist_voice_of_reason, "&Voice of Reason");
    menuUZ->Append(id_runewordlist_void, "&Void");
    menuUZ->Append(id_runewordlist_wealth, "&Wealth");
    menuUZ->Append(id_runewordlist_white, "&White");
    menuUZ->Append(id_runewordlist_wind, "&Wind");
    menuUZ->Append(id_runewordlist_wisdom, "&Wisdom");
    menuUZ->Append(id_runewordlist_wrath, "&Wrath");
    menuUZ->Append(id_runewordlist_zephyr, "&Zephyr");


    // BREAKPOINTS MENU
    wxMenu *menuBreakpoints = new wxMenu();
    menuBar->Append(menuBreakpoints, "&Breakpoints");

    // amazon submenu
    wxMenu *menuAmazon = new wxMenu();
    menuBreakpoints->Append(wxID_ANY, "&Amazon", menuAmazon);
    menuAmazon->Append(id_breakpoints_amazon_ibs, "&Increased Blocking Speed");
    menuAmazon->Append(id_breakpoints_amazon_fcr, "&Faster Cast Rate");
    menuAmazon->Append(id_breakpoints_amazon_fhr, "&Faster Hit Recovery");

    // assassin submenu
    wxMenu *menuAssassin = new wxMenu();
    menuBreakpoints->Append(wxID_ANY, "&Assassin", menuAssassin);
    menuAssassin->Append(id_breakpoints_assassin_ibs, "&Increased Blocking Speed");
    menuAssassin->Append(id_breakpoints_assassin_fcr, "&Faster Cast Rate");
    menuAssassin->Append(id_breakpoints_assassin_fhr, "&Faster Hit Recovery");

    // barbarian submenu
    wxMenu *menuBarbarian = new wxMenu();
    menuBreakpoints->Append(wxID_ANY, "&Barbarian", menuBarbarian);
    menuBarbarian->Append(id_breakpoints_barbarian_ibs, "&Increased Blocking Speed");
    menuBarbarian->Append(id_breakpoints_barbarian_fcr, "&Faster Cast Rate");
    menuBarbarian->Append(id_breakpoints_barbarian_fhr, "&Faster Hit Recovery");

    // druid submenu
    wxMenu *menuDruid = new wxMenu();
    menuBreakpoints->Append(wxID_ANY, "&Druid", menuDruid);
    menuDruid->Append(id_breakpoints_druid_ibs, "&Increased Blocking Speed");
    menuDruid->Append(id_breakpoints_druid_fcr, "&Faster Cast Rate");
    menuDruid->Append(id_breakpoints_druid_fhr, "&Faster Hit Recovery");

    // necromancer submenu
    wxMenu *menuNecromancer = new wxMenu();
    menuBreakpoints->Append(wxID_ANY, "&Necromancer", menuNecromancer);
    menuNecromancer->Append(id_breakpoints_necromancer_ibs, "&Increased Blocking Speed");
    menuNecromancer->Append(id_breakpoints_necromancer_fcr, "&Faster Cast Rate");
    menuNecromancer->Append(id_breakpoints_necromancer_fhr, "&Faster Hit Recovery");

    // paladin submenu
    wxMenu *menuPaladin = new wxMenu();
    menuBreakpoints->Append(wxID_ANY, "&Paladin", menuPaladin);
    menuPaladin->Append(id_breakpoints_paladin_ibs, "&Increased Blocking Speed");
    menuPaladin->Append(id_breakpoints_paladin_fcr, "&Faster Cast Rate");
    menuPaladin->Append(id_breakpoints_paladin_fhr, "&Faster Hit Recovery");

    // sorceress submenu
    wxMenu *menuSorceress = new wxMenu();
    menuBreakpoints->Append(wxID_ANY, "&Sorceress", menuSorceress);
    menuSorceress->Append(id_breakpoints_sorceress_ibs, "&Increased Blocking Speed");
    menuSorceress->Append(id_breakpoints_sorceress_fcr, "&Faster Cast Rate");
    menuSorceress->Append(id_breakpoints_sorceress_fhr, "&Faster Hit Recovery");

    // warlock submenu
    wxMenu *menuWarlock = new wxMenu();
    menuBreakpoints->Append(wxID_ANY, "&Warlock", menuWarlock);
    menuWarlock->Append(id_breakpoints_warlock_ibs, "&Increased Blocking Speed");
    menuWarlock->Append(id_breakpoints_warlock_fcr, "&Faster Cast Rate");
    menuWarlock->Append(id_breakpoints_warlock_fhr, "&Faster Hit Recovery");

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);

    cb_el = new wxCheckBox(checkbox_panel, id_cb_el, "El", wxPoint(0, 0));
    cb_el->SetValue(true);
    wxString el_tooltip = "El Rune:\n\n\
Weapon\t\t\t+50 to Attack Rating\n\
\t\t\t+1 to Light Radius\n\n\
Shield\t\t\t+15 Defense\n\
\t\t\t+1 to Light Radius\n\n\
Armor\t\t\t+15 Defense\n\
\t\t\t+1 to Light Radius\n\n\
Cube\n\
Create this rune\t\tNot possible\n\
Upgrade this rune\t\t3 El = Eld";
    cb_el->SetToolTip(el_tooltip);


    cb_eld = new wxCheckBox(checkbox_panel, id_cb_eld, "Eld", wxPoint(60, 0));
    cb_eld->SetValue(true);
    wxString eld_tooltip = "Eld Rune:\n\n\
Weapon\t\t\t+75% Damage To Undead\n\
\t\t\t+50 Atk Rating Vs Undead\n\n\
Shield\t\t\t+7% Chance of Blocking\n\n\
Armor\t\t\t15% Slower Stamina Drain\n\n\
Cube\n\
Create this rune\t\t3 El = Eld\n\
Upgrade this rune\t\t3 Eld = Tir";
    cb_eld->SetToolTip(eld_tooltip);

    cb_tir = new wxCheckBox(checkbox_panel, id_cb_tir, "Tir", wxPoint(120, 0));
    cb_tir->SetValue(true);
    wxString tir_tooltip = "Tir Rune:\n\n\
Weapon\t\t\t+2 To Mana After Each Kill\n\n\
Shield\t\t\t+2 To Mana After Each Kill\n\n\
Armor\t\t\t+2 To Mana After Each Kill\n\n\
Cube\n\
Create this rune\t\t3 Eld = Tir\n\
Upgrade this rune\t\t3 Tir = Nef";
    cb_tir->SetToolTip(tir_tooltip);

    cb_nef = new wxCheckBox(checkbox_panel, id_cb_nef, "Nef", wxPoint(0, 30));
    cb_nef->SetValue(true);
    wxString nef_tooltip = "Nef Rune:\n\n\
Weapon\t\t\tKnockback\n\n\
Shield\t\t\t+30 Defense vs. Missile\n\n\
Armor\t\t\t+30 Defense vs. Missile\n\n\
Cube\n\
Create this rune\t\t3 Tir = Nef\n\
Upgrade this rune\t\t3 Nef = Eth";
    cb_nef->SetToolTip(nef_tooltip);

    cb_eth = new wxCheckBox(checkbox_panel, id_cb_eth, "Eth", wxPoint(60, 30));
    cb_eth->SetValue(true);
    wxString eth_tooltip = "Eth Rune:\n\n\
Weapon\t\t\t-25% To Target Defense\n\n\
Shield\t\t\tRegenerate Mana 15%\n\n\
Armor\t\t\tRegenerate Mana 15%\n\n\
Cube\n\
Create this rune\t\t3 Nef = Eth\n\
Upgrade this rune\t\t3 Eth = Ith";
    cb_eth->SetToolTip(eth_tooltip);

    cb_ith = new wxCheckBox(checkbox_panel, id_cb_ith, "Ith", wxPoint(120, 30));
    cb_ith->SetValue(true);
    wxString ith_tooltip = "Ith Rune:\n\n\
Weapo\t\t\t+9 To Maximum Dmg\n\n\
Shield\t\t\t15% Dmg Taken to Mana\n\n\
Armor\t\t\t15% Dmg Taken to Mana\n\n\
Cube\n\
Create this rune\t\t3 Eth = Ith\n\
Upgrade this rune\t\t3 Ith = Tal";
    cb_ith->SetToolTip(ith_tooltip);

    cb_tal = new wxCheckBox(checkbox_panel, id_cb_tal, "Tal", wxPoint(0, 60));
    cb_tal->SetValue(true);
    wxString tal_tooltip = "Tal Rune:\n\n\
Weapon\t\t\t+75 Poison Dmg (5 Sec)\n\n\
Shield\t\t\tPoison Resist 30%\n\n\
Armor\t\t\tPoison Resist 30%\n\n\
Cube\n\
Create this rune\t\t3 Ith = Tal\n\
Upgrade this rune\t\t3 Tal = Ral";
    cb_tal->SetToolTip(tal_tooltip);

    cb_ral = new wxCheckBox(checkbox_panel, id_cb_ral, "Ral", wxPoint(60, 60));
    cb_ral->SetValue(true);
    wxString ral_tooltip = "Ral Rune:\n\n\
Weapon\t\t\tAdds 5-30 Fire Damage\n\n\
Shield\t\t\tFire Resist 30%\n\n\
Armor\t\t\tFire Resist 30%\n\n\
Cube\n\
Create this rune\t\t3 Tal = Ral\n\
Upgrade this rune\t\t3 Ral = Ort";
    cb_ral->SetToolTip(ral_tooltip);

    cb_ort = new wxCheckBox(checkbox_panel, id_cb_ort, "Ort", wxPoint(120, 60));
    cb_ort->SetValue(true);
    wxString ort_tooltip = "Ort Rune:\n\n\
Weapon\t\t\tAdds 1-50 Lightn. Dmg\n\n\
Shield\t\t\tLightning Resist 30%\n\n\
Armor\t\t\tLightning Resist 30%\n\n\
Cube\n\
Create this rune\t\t3 Ral = Ort\n\
Upgrade this rune\t\t3 Ort = Thul";
    cb_ort->SetToolTip(ort_tooltip);

    cb_thul = new wxCheckBox(checkbox_panel, id_cb_thul, "Thul",
                wxPoint(0, 90));
    cb_thul->SetValue(true);
    wxString thul_tooltip = "Thul Rune:\n\n\
Weapon\t\tAdds 3-14 Cold Damage\n\n\
Shield\t\tCold Resist 35%\n\n\
Armor\t\tCold Resist 30%\n\n\
Cube\n\
Create this rune\t3 Ort = Thul\n\
Upgrade this rune\t3 Thul + Chipped Topaz = Amn";
    cb_thul->SetToolTip(thul_tooltip);

    cb_amn = new wxCheckBox(checkbox_panel, id_cb_amn, "Amn", wxPoint(60, 90));
    cb_amn->SetValue(true);
    wxString amn_tooltip = "Amn Rune:\n\n\
Weapon\t\t7% Life Stolen Per Hit\n\n\
Shield\t\tAttacker Takes Dmg of 14\n\n\
Armor\t\tAttacker Takes Dmg of 14\n\n\
Cube\n\
Create this rune\t3 Thul + Chipped Topaz = Amn\n\
Upgrade this rune\t3 Amn + Chipped Amethyst = Sol";
    cb_amn->SetToolTip(amn_tooltip);

    cb_sol = new wxCheckBox(checkbox_panel, id_cb_sol, "Sol", wxPoint(120, 90));
    cb_sol->SetValue(true);
    wxString sol_tooltip = "Sol Rune:\n\n\
Weapon\t\t+9 To Minimum Damage\n\n\
Shield\t\tDamage Reduced By 7\n\n\
Armor\t\tDamage Reduced By 7\n\n\
Cube\n\
Create this rune\t3 Amn + Chipped Amethyst = Sol\n\
Upgrade this rune\t3 Sol + Chipped Sapphire = Shael";
    cb_sol->SetToolTip(sol_tooltip);

    cb_shael = new wxCheckBox(checkbox_panel, id_cb_shael, "Shael",
                wxPoint(0, 120));
    cb_shael->SetValue(true);
    wxString shael_tooltip = "Shael Rune:\n\n\
Weapon\t\t20% Increased Attack Speed\n\n\
Shield\t\t20% Faster Block Rate\n\n\
Armor\t\t20% Faster Hit Recovery\n\n\
Cube\n\
Create this rune\t3 Sol + Chipped Sapphire = Shael\n\
Upgrade this rune\t3 Shael + Chipped Ruby = Dol";
    cb_shael->SetToolTip(shael_tooltip);

    cb_dol = new wxCheckBox(checkbox_panel, id_cb_dol, "Dol", wxPoint(60, 120));
    cb_dol->SetValue(true);
    wxString dol_tooltip = "Dol Rune:\n\n\
Weapon\t\tHit Causes Monster To Flee +25%\n\n\
Shield\t\tReplenish Life +7\n\n\
Armor\t\tReplenish Life +7\n\n\
Cube\n\
Create this rune\t3 Shael + Chipped Ruby = Dol\n\
Upgrade this rune\t3 Dol + Chipped Emerald = Hel";
    cb_dol->SetToolTip(dol_tooltip);

    cb_hel = new wxCheckBox(checkbox_panel, id_cb_hel, "Hel",
                wxPoint(120, 120));
    cb_hel->SetValue(true);
    wxString hel_tooltip = "Hel Rune:\n\n\
Weapon\t\tRequirements -20%\n\n\
Shield\t\tRequirements -15%\n\n\
Armor\t\tRequirements -15%\n\n\
Cube\n\
Create this rune\t3 Dol + Chipped Emerald = Hel\n\
Upgrade this rune\t3 Hel + Chipped Diamond = Io";
    cb_hel->SetToolTip(hel_tooltip);

    cb_io = new wxCheckBox(checkbox_panel, id_cb_io, "Io", wxPoint(0, 150));
    cb_io->SetValue(true);
    wxString io_tooltip = "Io Rune:\n\n\
Weapon\t\t+10 To Vitality\n\n\
Shield\t\t+10 To Vitality\n\n\
Armor\t\t+10 To Vitality\n\n\
Cube\n\
Create this rune\t3 Hel + Chipped Diamond = Io\n\
Upgrade this rune\t3 Io + Flawed Topaz = Lum";
    cb_io->SetToolTip(io_tooltip);

    cb_lum = new wxCheckBox(checkbox_panel, id_cb_lum, "Lum", wxPoint(60, 150));
    cb_lum->SetValue(true);
    wxString lum_tooltip = "Lum Rune:\n\n\
Weapon\t\t+10 To Energy\n\n\
Shield\t\t+10 To Energy\n\n\
Armor\t\t+10 To Energy\n\n\
Cube\n\
Create this rune\t3 Io + Flawed Topaz = Lum\n\
Upgrade this rune\t3 Lum + Flawed Amethyst = Ko";
    cb_lum->SetToolTip(lum_tooltip);

    cb_ko = new wxCheckBox(checkbox_panel, id_cb_ko, "Ko", wxPoint(120, 150));
    cb_ko->SetValue(true);
    wxString ko_tooltip = "Ko Rune:\n\n\
Weapon\t\t+10 To Dexterity\n\n\
Shield\t\t+10 To Dexterity\n\n\
Armor\t\t+10 To Dexterity\n\n\
Cube\n\
Create this rune\t3 Lum + Flawed Amethyst = Ko\n\
Upgrade this rune\t3 Ko + Flawed Sapphire = Fal";
    cb_ko->SetToolTip(ko_tooltip);

    cb_fal = new wxCheckBox(checkbox_panel, id_cb_fal, "Fal", wxPoint(0, 180));
    cb_fal->SetValue(true);
    wxString fal_tooltip = "Fal Rune:\n\n\
Weapon\t\t+10 To Strength\n\n\
Shield\t\t+10 To Strength\n\n\
Armor\t\t+10 To Strength\n\n\
Cube\n\
Create this rune\t3 Ko + Flawed Sapphire = Fal\n\
Upgrade this rune\t3 Fal + Flawed Ruby = Lem";
    cb_fal->SetToolTip(fal_tooltip);

    cb_lem = new wxCheckBox(checkbox_panel, id_cb_lem, "Lem", wxPoint(60, 180));
    cb_lem->SetValue(true);
    wxString lem_tooltip = "Lem Rune:\n\n\
Weapon\t\t75% Extra Gold From Monsters\n\n\
Shield\t\t50% Extra Gold From Monsters\n\n\
Armor\t\t50% Extra Gold From Monsters\n\n\
Cube\n\
Create this rune\t3 Fal + Flawed Ruby = Lem\n\
Upgrade this rune\t3 Lem + Flawed Emerald = Pul";
    cb_lem->SetToolTip(lem_tooltip);

    cb_pul = new wxCheckBox(checkbox_panel, id_cb_pul, "Pul",
            wxPoint(120, 180));
    cb_pul->SetValue(true);
    wxString pul_tooltip = "Pul Rune:\n\n\
Weapon\t\t+75% Damage To Demons\n\
\t\t+100 Attack Rating vs. Demons\n\n\
Shield\t\t+30% Enhanced Defense\n\n\
Armor\t\t+30% Enhanced Defense\n\n\
Cube\n\
Create this rune\t3 Lem + Flawed Emerald = Pul\n\
Upgrade this rune\t2 Pul + Flawed Diamond = Um";
    cb_pul->SetToolTip(pul_tooltip);

    cb_um = new wxCheckBox(checkbox_panel, id_cb_um, "Um", wxPoint(0, 210));
    cb_um->SetValue(true);
    wxString um_tooltip = "Um Rune:\n\n\
Weapon\t\t+25% Chance of Open Wounds\n\n\
Shield\t\tAll Resistances +22\n\n\
Armor\t\tAll Resistances +15\n\n\
Cube\n\
Create this rune\t2 Pul + Flawed Diamond = Um\n\
Upgrade this rune\t2 Um + Topaz = Mal";
    cb_um->SetToolTip(um_tooltip);

    cb_mal = new wxCheckBox(checkbox_panel, id_cb_mal, "Mal", wxPoint(60, 210));
    cb_mal->SetValue(true);
    wxString mal_tooltip = "Mal Rune:\n\n\
Weapon\t\tPrevent Monster Heal\n\n\
Shield\t\tMagic Damage Reduced By 7\n\n\
Armor\t\tMagic Damage Reduced By 7\n\n\
Cube\n\
Create this rune\t2 Um + Topaz = Mal\n\
Upgrade this rune\t2 Mal + Amethyst = Ist";
    cb_mal->SetToolTip(mal_tooltip);

    cb_ist = new wxCheckBox(checkbox_panel, id_cb_ist, "Ist",
                wxPoint(120, 210));
    cb_ist->SetValue(true);
    wxString ist_tooltip = "Ist Rune:\n\n\
Weapon\t\t30% Magic Find\n\n\
Shield\t\t25% Magic Find\n\n\
Armor\t\t25% Magic Find\n\n\
Cube\n\
Create this rune\t2 Mal + Amethyst = Ist\n\
Upgrade this rune\t2 Ist + Sapphire = Gul";
    cb_ist->SetToolTip(ist_tooltip);

    cb_gul = new wxCheckBox(checkbox_panel, id_cb_gul, "Gul", wxPoint(0, 240));
    cb_gul->SetValue(true);
    wxString gul_tooltip = "Gul Rune:\n\n\
Weapon\t\t20% Bonus To Attack Rating\n\n\
Shield\t\t5% To Maximum Poison Resist\n\n\
Armor\t\t5% To Maximum Poison Resist\n\n\
Cube\n\
Create this rune\t2 Ist + Sapphire = Gul\n\
Upgrade this rune\t2 Gul + Ruby = Vex";
    cb_gul->SetToolTip(gul_tooltip);

    cb_vex = new wxCheckBox(checkbox_panel, id_cb_vex, "Vex", wxPoint(60, 240));
    cb_vex->SetValue(true);
    wxString vex_tooltip = "Vex Rune:\n\n\
Weapon\t\t7% Mana Stolen Per Hit\n\n\
Shield\t\t5% To Maximum Fire Resist\n\n\
Armor\t\t5% To Maximum Fire Resist\n\n\
Cube\n\
Create this rune\t2 Gul + Ruby = Vex\n\
Upgrade this rune\t2 Vex + Emerald = Ohm";
    cb_vex->SetToolTip(vex_tooltip);

    cb_ohm = new wxCheckBox(checkbox_panel, id_cb_ohm, "Ohm",
                wxPoint(120, 240));
    cb_ohm->SetValue(true);
    wxString ohm_tooltip = "Ohm Rune:\n\n\
Weapon\t\t+50% Enhanced Damage\n\n\
Shield\t\t5% To Maximum Cold Resist\n\n\
Armor\t\t5% To Maximum Cold Resist\n\n\
Cube\n\
Create this rune\t2 Vex + Emerald = Ohm\n\
Upgrade this rune\t2 Ohm + Diamond = Lo";
    cb_ohm->SetToolTip(ohm_tooltip);

    cb_lo = new wxCheckBox(checkbox_panel, id_cb_lo, "Lo", wxPoint(0, 270));
    cb_lo->SetValue(true);
    wxString lo_tooltip = "Lo Rune:\n\n\
Weapon\t\t+20% Deadly Strike\n\n\
Shield\t\t5% To Max Lightning Resist\n\n\
Armor\t\t5% To Max Lightning Resist\n\n\
Cube\n\
Create this rune\t2 Ohm + Diamond = Lo\n\
Upgrade this rune\t2 Lo + Flawless Topaz = Sur";
    cb_lo->SetToolTip(lo_tooltip);

    cb_sur = new wxCheckBox(checkbox_panel, id_cb_sur, "Sur", wxPoint(60, 270));
    cb_sur->SetValue(true);
    wxString sur_tooltip = "Sur Rune:\n\n\
Weapon\t\tHit Blinds Target\n\n\
Shield\t\t+50 To Mana\n\n\
Armor\t\t5% To Maximum Mana\n\n\
Cube\n\
Create this rune\t2 Lo + Flawless Topaz = Sur\n\
Upgrade this rune\t2 Sur + Flawless Amethyst = Ber";
    cb_sur->SetToolTip(sur_tooltip);

    cb_ber = new wxCheckBox(checkbox_panel, id_cb_ber, "Ber",
                wxPoint(120, 270));
    cb_ber->SetValue(true);
    wxString ber_tooltip = "Ber Rune:\n\n\
Weapon\t\t+20% Crushing Blow Chance\n\n\
Shield\t\tDamage Reduced by 8%\n\n\
Armor\t\tDamage Reduced by 8%\n\n\
Cube\n\
Create this rune\t2 Sur + Flawless Amethyst = Ber\n\
Upgrade this rune\t2 Ber + Flawless Sapphire = Jah";
    cb_ber->SetToolTip(ber_tooltip);

    cb_jah = new wxCheckBox(checkbox_panel, id_cb_jah, "Jah", wxPoint(0, 300));
    cb_jah->SetValue(true);
    wxString jah_tooltip = "Jah Rune:\n\n\
Weapon\t\tIgnore Target's Defense\n\n\
Shield\t\t+50 Life\n\n\
Armor\t\tIncrease Maximum Life 5%\n\n\
Cube\n\
Create this rune\t2 Ber + Flawless Sapphire = Jah\n\
Upgrade this rune\t2 Jah + Flawless Ruby = Cham";
    cb_jah->SetToolTip(jah_tooltip);

    cb_cham = new wxCheckBox(checkbox_panel, id_cb_cham, "Cham",
                wxPoint(60, 300));
    cb_cham->SetValue(true);
    wxString cham_tooltip = "Cham Rune:\n\n\
Weapon\t\tFreeze Target +3\n\n\
Shield\t\tCannot Be Frozen\n\n\
Armor\t\tCannot Be Frozen\n\n\
Cube\n\
Create this rune\t2 Jah + Flawless Ruby = Cham\n\
Upgrade this rune\t2 Cham + Flawless Emerald = Zod";
    cb_cham->SetToolTip(cham_tooltip);

    cb_zod = new wxCheckBox(checkbox_panel, id_cb_zod, "Zod",
                wxPoint(120, 300));
    cb_zod->SetValue(true);
    wxString zod_tooltip = "Zod Rune:\n\n\
Weapon\t\tIndestructible\n\n\
Shield\t\tIndestructible\n\n\
Armor\t\tIndestructible\n\n\
Cube\n\
Create this rune\t2 Cham + Flawless Emerald = Zod\n\
Upgrade this rune\tNot possible";
    cb_zod->SetToolTip(zod_tooltip);

    set_cb_pointers = {cb_el, cb_eld, cb_tir, cb_nef,
    cb_eth, cb_ith, cb_tal, cb_ral, cb_ort, cb_thul, cb_amn, cb_sol, cb_shael,
    cb_dol, cb_hel, cb_io, cb_lum, cb_ko, cb_fal, cb_lem, cb_pul, cb_um, cb_mal,
    cb_ist, cb_gul, cb_vex, cb_ohm, cb_lo, cb_sur,
    cb_ber, cb_jah, cb_cham, cb_zod};


    // widget: button invert
    wxButton *btn_invert = new wxButton(btn_panel_invert, id_btn_invert,
        "Invert", wxPoint(0, 0), wxSize(160, 40));
    btn_invert->SetToolTip(wxT("Invert Rune Selection"));

    // widget: button reset
    wxButton *btn_reset = new wxButton(btn_panel_reset, id_btn_reset,
        "Reset", wxPoint(0, 0), wxSize(160, 40));
    btn_reset->SetToolTip(wxT("Reset Rune Selection"));

    // widget: button sort (has been pre-defined in h file so that it is accessible everywhere)
    btn_sort = new wxButton(btn_panel_sort, id_btn_sort,
        "Sort A-Z", wxPoint(0, 0), wxSize(160, 40));
    btn_sort->SetToolTip(wxT("Changes Rune Sorting Order (Alphabetical vs Rarity)"));


    // widget: button calc
    wxButton *btn_calc = new wxButton(btn_panel_calc, id_btn_calc,
        "Calculate Runewords", wxPoint(0, 0), wxSize(200, 50));
    btn_calc->SetToolTip(wxT("Calculates All Possible Runewords"));

    // add custom message at the bottom
    CreateStatusBar();
    SetStatusText("");

    Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);

    // breakpoints, assign menubar clicks to function calls

    // amazon
    Bind(wxEVT_MENU, &MainFrame::OnBreakpointsAmazonIBS, this, id_breakpoints_amazon_ibs);
    Bind(wxEVT_MENU, &MainFrame::OnBreakpointsAmazonFCR, this, id_breakpoints_amazon_fcr);
    Bind(wxEVT_MENU, &MainFrame::OnBreakpointsAmazonFHR, this, id_breakpoints_amazon_fhr);

    // assassin
    Bind(wxEVT_MENU, &MainFrame::OnBreakpointsAssassinIBS, this, id_breakpoints_assassin_ibs);
    Bind(wxEVT_MENU, &MainFrame::OnBreakpointsAssassinFCR, this, id_breakpoints_assassin_fcr);
    Bind(wxEVT_MENU, &MainFrame::OnBreakpointsAssassinFHR, this, id_breakpoints_assassin_fhr);


    // barbarian
    Bind(wxEVT_MENU, &MainFrame::OnBreakpointsBarbarianIBS, this, id_breakpoints_barbarian_ibs);
    Bind(wxEVT_MENU, &MainFrame::OnBreakpointsBarbarianFCR, this, id_breakpoints_barbarian_fcr);
    Bind(wxEVT_MENU, &MainFrame::OnBreakpointsBarbarianFHR, this, id_breakpoints_barbarian_fhr);


    // druid
    Bind(wxEVT_MENU, &MainFrame::OnBreakpointsDruidIBS, this, id_breakpoints_druid_ibs);
    Bind(wxEVT_MENU, &MainFrame::OnBreakpointsDruidFCR, this, id_breakpoints_druid_fcr);
    Bind(wxEVT_MENU, &MainFrame::OnBreakpointsDruidFHR, this, id_breakpoints_druid_fhr);

    // necromancer
    Bind(wxEVT_MENU, &MainFrame::OnBreakpointsNecromancerIBS, this, id_breakpoints_necromancer_ibs);
    Bind(wxEVT_MENU, &MainFrame::OnBreakpointsNecromancerFCR, this, id_breakpoints_necromancer_fcr);
    Bind(wxEVT_MENU, &MainFrame::OnBreakpointsNecromancerFHR, this, id_breakpoints_necromancer_fhr);

    // paladin
    Bind(wxEVT_MENU, &MainFrame::OnBreakpointsPaladinIBS, this, id_breakpoints_paladin_ibs);
    Bind(wxEVT_MENU, &MainFrame::OnBreakpointsPaladinFCR, this, id_breakpoints_paladin_fcr);
    Bind(wxEVT_MENU, &MainFrame::OnBreakpointsPaladinFHR, this, id_breakpoints_paladin_fhr);

    // sorceress
    Bind(wxEVT_MENU, &MainFrame::OnBreakpointsSorceressIBS, this, id_breakpoints_sorceress_ibs);
    Bind(wxEVT_MENU, &MainFrame::OnBreakpointsSorceressFCR, this, id_breakpoints_sorceress_fcr);
    Bind(wxEVT_MENU, &MainFrame::OnBreakpointsSorceressFHR, this, id_breakpoints_sorceress_fhr);

    // warlock
    Bind(wxEVT_MENU, &MainFrame::OnBreakpointsWarlockIBS, this, id_breakpoints_warlock_ibs);
    Bind(wxEVT_MENU, &MainFrame::OnBreakpointsWarlockFCR, this, id_breakpoints_warlock_fcr);
    Bind(wxEVT_MENU, &MainFrame::OnBreakpointsWarlockFHR, this, id_breakpoints_warlock_fhr);

    // bind all runeword list menu items
    for (int ez = id_runewordlist_ancients_pledge; ez <= id_runewordlist_zephyr; ez++){
        Bind(wxEVT_MENU, &MainFrame::OnRunewordListSelectionClick, this, ez);
    }

}


void MainFrame::OnExit(wxCommandEvent &event){
    Close(true);
}



void MainFrame::OnAbout(wxCommandEvent &event){
    wxMessageBox("Hey, if you find any bugs or false information please send me an E-Mail:\nf3lix.dev@gmx.de\n\nIf you have good ideas, feel free to tell me which features you would like to see!\n\
\nProgram Version: 3.0",
                 "About", wxOK | wxICON_INFORMATION); // this line is the title of the info box that opens
}

// breakpoint tables use tab separators to avoid manual space padding
void MainFrame::OnBreakpointsAmazonIBS(wxCommandEvent& event) {
    ShowBreakpointDialog(this, "Amazon IBS Breakpoints", "Amazon\n\n\
Increased Blocking Speed	Frames\n\n\
1H Swinging Weapon:\n\
0	17\n\
4	16\n\
6	15\n\
11	14\n\
15	13\n\
23	12\n\
29	11\n\
40	10\n\
56	9\n\
80	8\n\
120	7\n\
200	6\n\
480	5\n\
\n\
Other Weapons:\n\
0	5\n\
13	4\n\
32	3\n\
86	2\n\
600	1\n\
");
}

void MainFrame::OnBreakpointsAmazonFCR(wxCommandEvent& event) {
    ShowBreakpointDialog(this, "Amazon FCR Breakpoints", "Amazon\n\n\
Faster Cast Rate	Frames\n\n\
0	19\n\
7	18\n\
14	17\n\
22	16\n\
32	15\n\
48	14\n\
68	13\n\
99	12\n\
152	11\n\
");
}

void MainFrame::OnBreakpointsAmazonFHR(wxCommandEvent& event) {
    ShowBreakpointDialog(this, "Amazon FHR Breakpoints", "Amazon\n\n\
Faster Hit Recovery	Frames\n\n\
0	11\n\
6	10\n\
13	9\n\
20	8\n\
32	7\n\
52	6\n\
86	5\n\
174	4\n\
600	3\n\
");
}

void MainFrame::OnBreakpointsAssassinIBS(wxCommandEvent& event) {
    ShowBreakpointDialog(this, "Assassin IBS Breakpoints", "Assassin\n\n\
Increased Blocking Speed	Frames\n\n\
0	5\n\
13	4\n\
32	3\n\
86	2\n\
600	1\n\
");
}

void MainFrame::OnBreakpointsAssassinFCR(wxCommandEvent& event) {
    ShowBreakpointDialog(this, "Assassin FCR Breakpoints", "Assassin\n\n\
Faster Cast Rate	Frames\n\n\
0	16\n\
8	15\n\
16	14\n\
27	13\n\
42	12\n\
65	11\n\
102	10\n\
174	9\n\
");
}

void MainFrame::OnBreakpointsAssassinFHR(wxCommandEvent& event) {
    ShowBreakpointDialog(this, "Assassin FHR Breakpoints", "Assassin\n\n\
Faster Hit Recovery	Frames\n\n\
0	9\n\
7	8\n\
15	7\n\
27	6\n\
48	5\n\
86	4\n\
200	3\n\
");
}

void MainFrame::OnBreakpointsBarbarianIBS(wxCommandEvent& event) {
    ShowBreakpointDialog(this, "Barbarian IBS Breakpoints", "Barbarian\n\n\
Increased Blocking Speed	Frames\n\n\
0	7\n\
9	6\n\
20	5\n\
42	4\n\
86	3\n\
280	2\n\
");
}

void MainFrame::OnBreakpointsBarbarianFCR(wxCommandEvent& event) {
    ShowBreakpointDialog(this, "Barbarian FCR Breakpoints", "Barbarian\n\n\
Faster Cast Rate	Frames\n\n\
0	13\n\
9	12\n\
20	11\n\
37	10\n\
63	9\n\
105	8\n\
200	7\n\
");
}

void MainFrame::OnBreakpointsBarbarianFHR(wxCommandEvent& event) {
    ShowBreakpointDialog(this, "Barbarian FHR Breakpoints", "Barbarian\n\n\
Faster Hit Recovery	Frames\n\n\
0	9\n\
7	8\n\
15	7\n\
27	6\n\
48	5\n\
86	4\n\
200	3\n\
");
}

void MainFrame::OnBreakpointsDruidIBS(wxCommandEvent& event) {
    ShowBreakpointDialog(this, "Druid IBS Breakpoints", "Druid\n\n\
Increased Blocking Speed	Frames\n\n\
Human Form\n\
0	11\n\
6	10\n\
13	9\n\
20	8\n\
32	7\n\
52	6\n\
86	5\n\
174	4\n\
600	3\n\n\
Bear Form\n\
0	12\n\
5	11\n\
10	10\n\
16	9\n\
27	8\n\
40	7\n\
65	6\n\
109	5\n\
223	4\n\n\
Wolf Form\n\
0	9\n\
7	8\n\
15	7\n\
27	6\n\
48	5\n\
86	4\n\
200	3\n\
");
}

void MainFrame::OnBreakpointsDruidFCR(wxCommandEvent& event) {
    ShowBreakpointDialog(this, "Druid FCR Breakpoints", "Druid\n\n\
Faster Cast Rate	Frames\n\n\
Human Form\n\
0	18\n\
4	17\n\
10	16\n\
19	15\n\
30	14\n\
46	13\n\
68	12\n\
99	11\n\
163	10\n\n\
Bear Form\n\
0	16\n\
7	15\n\
15	14\n\
26	13\n\
40	12\n\
63	11\n\
99	10\n\
163	9\n\n\
Wolf Form\n\
0	16\n\
6	15\n\
14	14\n\
26	13\n\
40	12\n\
60	11\n\
95	10\n\
157	9\n\
");
}

void MainFrame::OnBreakpointsDruidFHR(wxCommandEvent& event) {
    ShowBreakpointDialog(this, "Druid FHR Breakpoints", "Druid\n\n\
Faster Hit Recovery	Frames\n\n\
Human Form\n\
1H Swinging Weapon\n\
0	14\n\
3	13\n\
7	12\n\
13	11\n\
19	10\n\
29	9\n\
42	8\n\
63	7\n\
99	6\n\
174	5\n\
456	4\n\n\
Human Form\n\
Other Weapons\n\
0	13\n\
5	12\n\
10	11\n\
16	10\n\
26	9\n\
39	8\n\
56	7\n\
86	6\n\
152	5\n\
377	4\n\n\
Bear Form\n\
0	13\n\
5	12\n\
10	11\n\
16	10\n\
24	9\n\
37	8\n\
54	7\n\
86	6\n\
152	5\n\
360	4\n\n\
Wolf Form\n\
0	7\n\
9	6\n\
20	5\n\
42	4\n\
86	3\n\
280	2\n\
");
}


void MainFrame::OnBreakpointsNecromancerIBS(wxCommandEvent& event) {
    ShowBreakpointDialog(this, "Necromancer IBS Breakpoints", "Necromancer\n\n\
Increased Blocking Speed	Frames\n\n\
0	11\n\
6	10\n\
13	9\n\
20	8\n\
32	7\n\
52	6\n\
86	5\n\
174	4\n\
600	3\n\n\
");
}

void MainFrame::OnBreakpointsNecromancerFCR(wxCommandEvent& event) {
    ShowBreakpointDialog(this, "Necromancer FCR Breakpoints", "Necromancer\n\n\
Faster Cast Rate	Frames\n\n\
Human\n\
0	15\n\
9	14\n\
18	13\n\
30	12\n\
48	11\n\
75	10\n\
125	9\n\n\
Vampire\n\
0	23\n\
6	22\n\
11	21\n\
18	20\n\
24	19\n\
35	18\n\
48	17\n\
65	16\n\
86	15\n\
120	14\n\
180	13\n\
");
}

void MainFrame::OnBreakpointsNecromancerFHR(wxCommandEvent& event) {
    ShowBreakpointDialog(this, "Necromancer FHR Breakpoints", "Necromancer\n\n\
Faster Hit Recovery	Frames\n\n\
Human\n\
0	13\n\
5	12\n\
10	11\n\
16	10\n\
26	9\n\
39	8\n\
56	7\n\
86	6\n\
152	5\n\
377	4\n\n\
Vampire\n\
0	15\n\
2	14\n\
6	13\n\
10	12\n\
16	11\n\
24	10\n\
34	9\n\
48	8\n\
72	7\n\
117	6\n\
208	5\n\
");
}

void MainFrame::OnBreakpointsPaladinIBS(wxCommandEvent& event) {
    ShowBreakpointDialog(this, "Paladin IBS Breakpoints", "Paladin\n\n\
Increased Blocking Speed	Frames\n\n\
Without Holy Shield:\n\
0	5\n\
13	4\n\
32	3\n\
86	2\n\
600	1\n\
\n\
With Holy Shield:\n\
0	2\n\
86	1\n\
");
}

void MainFrame::OnBreakpointsPaladinFCR(wxCommandEvent& event) {
    ShowBreakpointDialog(this, "Paladin FCR Breakpoints", "Paladin\n\n\
Faster Cast Rate	Frames\n\n\
0	15\n\
9	14\n\
18	13\n\
30	12\n\
48	11\n\
75	10\n\
125	9\n\
");
}

void MainFrame::OnBreakpointsPaladinFHR(wxCommandEvent& event) {
    ShowBreakpointDialog(this, "Paladin FHR Breakpoints", "Paladin\n\n\
Faster Hit Recovery	Frames\n\n\
Spears and Staves\n\
0	13\n\
3	12\n\
7	11\n\
13	10\n\
20	9\n\
32	8\n\
48	7\n\
75	6\n\
129	5\n\
280	4\n\n\
Other Weapons\n\
0	9\n\
7	8\n\
15	7\n\
27	6\n\
48	5\n\
86	4\n\
200	3\n\
");
}

void MainFrame::OnBreakpointsSorceressIBS(wxCommandEvent& event) {
    ShowBreakpointDialog(this, "Sorceress IBS Breakpoints", "Sorceress\n\n\
Increased Blocking Speed	Frames\n\n\
0	9\n\
7	8\n\
15	7\n\
27	6\n\
48	5\n\
86	4\n\
200	3\n\
");
}

void MainFrame::OnBreakpointsSorceressFCR(wxCommandEvent& event) {
    ShowBreakpointDialog(this, "Sorceress FCR Breakpoints", "Sorceress\n\n\
Faster Cast Rate	Frames\n\n\
(Chain) Lightning\n\
0	19\n\
7	18\n\
15	17\n\
23	16\n\
35	15\n\
52	14\n\
78	13\n\
117	12\n\
194	11\n\n\
Other Spells\n\
0	13\n\
9	12\n\
20	11\n\
37	10\n\
63	9\n\
105	8\n\
200	7\n\
");
}

void MainFrame::OnBreakpointsSorceressFHR(wxCommandEvent& event) {
    ShowBreakpointDialog(this, "Sorceress FHR Breakpoints", "Sorceress\n\n\
Faster Hit Recovery	Frames\n\n\
0	15\n\
5	14\n\
9	13\n\
14	12\n\
20	11\n\
30	10\n\
42	9\n\
60	8\n\
86	7\n\
142	6\n\
280	5\n\
");
}

void MainFrame::OnBreakpointsWarlockIBS(wxCommandEvent& event) {
    ShowBreakpointDialog(this, "Warlock IBS Breakpoints", "Warlock\n\n\
Increased Blocking Speed	Frames\n\n\
0	11\n\
6	10\n\
13	9\n\
20	8\n\
32	7\n\
52	6\n\
86	5\n\
");
}

void MainFrame::OnBreakpointsWarlockFCR(wxCommandEvent& event) {
    ShowBreakpointDialog(this, "Warlock FCR Breakpoints", "Warlock\n\n\
Faster Cast Rate	Frames\n\n\
0	15\n\
9	14\n\
18	13\n\
30	12\n\
48	11\n\
75	10\n\
125	9\n\
");
}

void MainFrame::OnBreakpointsWarlockFHR(wxCommandEvent& event) {
    ShowBreakpointDialog(this, "Warlock FHR Breakpoints", "Warlock\n\n\
Faster Hit Recovery	Frames\n\n\
0	13\n\
5	12\n\
10	11\n\
16	10\n\
26	9\n\
39	8\n\
56	7\n\
86	6\n\
152	5\n\
377	4\n\
");
}

void MainFrame::OnRunewordListSelectionClick(wxCommandEvent &event){
    const int selection_id = event.GetId();
    wxMenuBar* menu_bar = GetMenuBar();
    wxMenuItem* clicked_item = (menu_bar == nullptr) ? nullptr : menu_bar->FindItem(selection_id);

    if (clicked_item == nullptr) {
        event.Skip();
        return;
    }

    const wxString runeword_name = clicked_item->GetItemLabelText();
    const string runeword_text = GetRunewordText(runeword_name.ToStdString());

    if (runeword_text.empty()) {
        event.Skip();
        return;
    }

    wxMessageBox(runeword_text, "Runeword Description", wxOK | wxICON_INFORMATION);

}


string MainFrame::GetRunewordText(string a){

    string final_text;

    for (Runeword r: runewords){
        if (r.name == a) {
            final_text = r.name + "\n\n" + r.runeword_stats + "\nRune Formula: " + r.runeword + "\nCompatible With: ";

            // list the compatible items (but there should be no semicolon after the last item)
            int compatible_items_amt = r.items.size();
            int counter_temp = 1;
            for (string s: r.items){
                if (counter_temp < compatible_items_amt){
                    final_text += s + ", ";
                }
                else {
                    final_text += s;
                }

                counter_temp += 1;
            }
            // dont care about the other runewords so lets stop searching
            break;
        }

    }

    return final_text;
}


void MainFrame::InvertRunes(wxCommandEvent &event){
    // invert all rune checkboxes
    for (wxCheckBox *cb: set_cb_pointers){
        if (cb->IsChecked()){
            cb->SetValue(false);
        }
        else {
            cb->SetValue(true);
        }

    }

}

void MainFrame::ResetRunes(wxCommandEvent &event){
    // check all rune checkboxes
    for (wxCheckBox *cb: set_cb_pointers){
        if (!(cb->IsChecked())){
            cb->SetValue(true);
        }
    }

}

void MainFrame::SortRunes(wxCommandEvent &event){
    // toggle sorting order between A-Z and by rarity
    if (btn_sort->GetLabelText() == "Sort A-Z"){
        for (wxCheckBox *cb: set_cb_pointers){
            if (cb->GetLabelText() == "Amn"){
                cb->Move(0, 0);
                
            }
            else if (cb->GetLabelText() == "Ber"){
                cb->Move(60, 0);
            }
            else if (cb->GetLabelText() == "Cham"){
                cb->Move(120, 0);
            }
            else if (cb->GetLabelText() == "Dol"){
                cb->Move(0, 30);
            }
            else if (cb->GetLabelText() == "El"){
                cb->Move(60, 30);
            }
            else if (cb->GetLabelText() == "Eld"){
                cb->Move(120, 30);
            }
            else if (cb->GetLabelText() == "Eth"){
                cb->Move(0, 60);
            }
            else if (cb->GetLabelText() == "Fal"){
                cb->Move(60, 60);
            }
            else if (cb->GetLabelText() == "Gul"){
                cb->Move(120, 60);
            }
            else if (cb->GetLabelText() == "Hel"){
                cb->Move(0, 90);
            }
            else if (cb->GetLabelText() == "Io"){
                cb->Move(60, 90);
            }
            else if (cb->GetLabelText() == "Ist"){
                cb->Move(120, 90);
            }
            else if (cb->GetLabelText() == "Ith"){
                cb->Move(0, 120);
            }
            else if (cb->GetLabelText() == "Jah"){
                cb->Move(60, 120);
            }
            else if (cb->GetLabelText() == "Ko"){
                cb->Move(120, 120);
            }
            else if (cb->GetLabelText() == "Lem"){
                cb->Move(0, 150);
            }
            else if (cb->GetLabelText() == "Lo"){
                cb->Move(60, 150);
            }
            else if (cb->GetLabelText() == "Lum"){
                cb->Move(120, 150);
            }
            else if (cb->GetLabelText() == "Mal"){
                cb->Move(0, 180);
            }
            else if (cb->GetLabelText() == "Nef"){
                cb->Move(60, 180);
            }
            else if (cb->GetLabelText() == "Ohm"){
                cb->Move(120, 180);
            }
            else if (cb->GetLabelText() == "Ort"){
                cb->Move(0, 210);
            }
            else if (cb->GetLabelText() == "Pul"){
                cb->Move(60, 210);
            }
            else if (cb->GetLabelText() == "Ral"){
                cb->Move(120, 210);
            }
            else if (cb->GetLabelText() == "Shael"){
                cb->Move(0, 240);
            }
            else if (cb->GetLabelText() == "Sol"){
                cb->Move(60, 240);
            }
            else if (cb->GetLabelText() == "Sur"){
                cb->Move(120, 240);
            }
            else if (cb->GetLabelText() == "Tal"){
                cb->Move(0, 270);
            }
            else if (cb->GetLabelText() == "Thul"){
                cb->Move(60, 270);
            }
            else if (cb->GetLabelText() == "Tir"){
                cb->Move(120, 270);
            }
            else if (cb->GetLabelText() == "Um"){
                cb->Move(0, 300);
            }
            else if (cb->GetLabelText() == "Vex"){
                cb->Move(60, 300);
            }
            else if (cb->GetLabelText() == "Zod"){
                cb->Move(120, 300);
            }

            cb->Refresh();   // required on windows otherwise text bugged until mouse is moved over it
        }
        
        btn_sort->SetLabelText("Sort By Rarity");

    }

    else if (btn_sort->GetLabelText() == "Sort By Rarity"){
        for (wxCheckBox *cb: set_cb_pointers){
            if (cb->GetLabelText() == "El"){
                cb->Move(0, 0);
            }
            else if (cb->GetLabelText() == "Eld"){
                cb->Move(60, 0);
            }
            else if (cb->GetLabelText() == "Tir"){
                cb->Move(120, 0);
            }
            else if (cb->GetLabelText() == "Nef"){
                cb->Move(0, 30);
            }
            else if (cb->GetLabelText() == "Eth"){
                cb->Move(60, 30);
            }
            else if (cb->GetLabelText() == "Ith"){
                cb->Move(120, 30);
            }
            else if (cb->GetLabelText() == "Tal"){
                cb->Move(0, 60);
            }
            else if (cb->GetLabelText() == "Ral"){
                cb->Move(60, 60);
            }
            else if (cb->GetLabelText() == "Ort"){
                cb->Move(120, 60);
            }
            else if (cb->GetLabelText() == "Thul"){
                cb->Move(0, 90);
            }
            else if (cb->GetLabelText() == "Amn"){
                cb->Move(60, 90);
            }
            else if (cb->GetLabelText() == "Sol"){
                cb->Move(120, 90);
            }
            else if (cb->GetLabelText() == "Shael"){
                cb->Move(0, 120);
            }
            else if (cb->GetLabelText() == "Dol"){
                cb->Move(60, 120);
            }
            else if (cb->GetLabelText() == "Hel"){
                cb->Move(120, 120);
            }
            else if (cb->GetLabelText() == "Io"){
                cb->Move(0, 150);
            }
            else if (cb->GetLabelText() == "Lum"){
                cb->Move(60, 150);
            }
            else if (cb->GetLabelText() == "Ko"){
                cb->Move(120, 150);
            }
            else if (cb->GetLabelText() == "Fal"){
                cb->Move(0, 180);
            }
            else if (cb->GetLabelText() == "Lem"){
                cb->Move(60, 180);
            }
            else if (cb->GetLabelText() == "Pul"){
                cb->Move(120, 180);
            }
            else if (cb->GetLabelText() == "Um"){
                cb->Move(0, 210);
            }
            else if (cb->GetLabelText() == "Mal"){
                cb->Move(60, 210);
            }
            else if (cb->GetLabelText() == "Ist"){
                cb->Move(120, 210);
            }
            else if (cb->GetLabelText() == "Gul"){
                cb->Move(0, 240);
            }
            else if (cb->GetLabelText() == "Vex"){
                cb->Move(60, 240);
            }
            else if (cb->GetLabelText() == "Ohm"){
                cb->Move(120, 240);
            }
            else if (cb->GetLabelText() == "Lo"){
                cb->Move(0, 270);
            }
            else if (cb->GetLabelText() == "Sur"){
                cb->Move(60, 270);
            }
            else if (cb->GetLabelText() == "Ber"){
                cb->Move(120, 270);
            }
            else if (cb->GetLabelText() == "Jah"){
                cb->Move(0, 300);
            }
            else if (cb->GetLabelText() == "Cham"){
                cb->Move(60, 300);
            }
            else if (cb->GetLabelText() == "Zod"){
                cb->Move(120, 300);
            }

            cb->Refresh();   // required on windows otherwise text bugged until mouse is moved over it
        }

        btn_sort->SetLabelText("Sort A-Z");

    }

}


void MainFrame::ShowRunewordStats(wxCommandEvent &event){
    // get label of current selection to choose correct runeword stats
    int cur_sel = result_listbox->GetSelection();
    if (cur_sel == wxNOT_FOUND) {
        return;
    }

    wxString cur_sel_label = result_listbox->GetString(cur_sel);

    // fix crash error when 'no possible runewords' string is selected
    if (cur_sel_label == wxT("No possible runewords.")) {
        return;
    }

    string temp5;

    // e.g. given Phoenix ("VexVexLoJah") extract "Phoenix" to identify runeword
    string str = cur_sel_label.ToStdString();
    const string separator = " (\"";
    const size_t name_end = str.find(separator);
    const string selected_name = (name_end == string::npos) ? str : str.substr(0, name_end);

    // go through all runewords and determine which runeword's stats are to be shown
    for (Runeword r: runewords){
        if (r.name == selected_name){
            temp5 = r.name + "\n\n" + r.runeword_stats;
            break;
        }
    }
    // convert std::string to wxString
    wxString runeword_stats_text(temp5);

    static_results->SetLabel(runeword_stats_text);
}


void MainFrame::DeleteResultCheckboxContents(){

    while (result_listbox->GetCount() > 0){
        // remove item with index 0
        result_listbox->Delete(0);
    }

}


void MainFrame::ClearResultCheckboxSelections(){
    wxArrayInt selections;
    int count = result_listbox->GetSelections(selections);

    for (int i=0; i<count; ++i){
      result_listbox->Deselect(selections[i]);
    }
}


void MainFrame::CalculateResults(wxCommandEvent &event){
    // first clear previous results
    MainFrame::DeleteResultCheckboxContents();

    // then clear runeword description box
    static_results->SetLabel(wxT(""));

    set<wxString> user_runes;
    for (wxCheckBox *cb: set_cb_pointers){
        if (cb->IsChecked()){
            user_runes.insert(cb->GetLabel());
        }
    }

    // now we have a set that contains all currently selected runes as strings


    wxString item_sel = choice_1->GetString((choice_1->GetSelection()));            // get chosen item type

    wxString temp2 = choice_2->GetString((choice_2->GetSelection()));               // get chosen socket amount and cast to int
    int user_sck = wxAtoi(temp2);

    wxString max_level_selection = choice_3->GetString((choice_3->GetSelection())); // get chosen max level


    // now calculate possible runewords
    vector<Runeword> results_final = actual_calc(user_runes, item_sel,
                                                    user_sck, max_level_selection);

    // and show them
    if (results_final.size() == 0){
        result_listbox->Append(wxT("No possible runewords."));
    }
    else{
        wxString rune_item;
        for (Runeword v: results_final){
            rune_item = v.name + " (\"" + v.runeword + "\")";
            result_listbox->Append(rune_item);
        }

    }

}
