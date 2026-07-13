#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/choice.h>
#include <wx/frame.h>
#include <wx/listbox.h>
#include <wx/log.h>
#include <wx/menu.h> // menu, menubar
#include <wx/msgdlg.h> //wxMessageBox
#include <wx/panel.h>
#include <wx/statline.h> //wxStaticLine
#include <wx/stattext.h>

#include <wx/textctrl.h>
#include <wx/richtooltip.h>

#include <set>
#include <vector>

#include "Runeword.h"

using std::set, std::vector;


enum id_enum{

    id_cb_el=0,
    id_cb_eld,
    id_cb_tir,
    id_cb_nef,
    id_cb_eth,
    id_cb_ith,
    id_cb_tal,
    id_cb_ral,
    id_cb_ort,
    id_cb_thul,
    id_cb_amn,
    id_cb_sol,
    id_cb_shael,
    id_cb_dol,
    id_cb_hel,
    id_cb_io,
    id_cb_lum,
    id_cb_ko,
    id_cb_fal,
    id_cb_lem,
    id_cb_pul,
    id_cb_um,
    id_cb_mal,
    id_cb_ist,
    id_cb_gul,
    id_cb_vex,
    id_cb_ohm,
    id_cb_lo,
    id_cb_sur,
    id_cb_ber,
    id_cb_jah,
    id_cb_cham,
    id_cb_zod,
    id_menu1,
    id_btn_calc,
    id_btn_invert,
    id_btn_reset,
    id_btn_sort,
    id_runeword_listbox,
    id_breakpoints_amazon_ibs,
    id_breakpoints_amazon_fcr,
    id_breakpoints_amazon_fhr,
    id_breakpoints_assassin_ibs,
    id_breakpoints_assassin_fcr,
    id_breakpoints_assassin_fhr,
    id_breakpoints_barbarian_ibs,
    id_breakpoints_barbarian_fcr,
    id_breakpoints_barbarian_fhr,
    id_breakpoints_druid_ibs,
    id_breakpoints_druid_fcr,
    id_breakpoints_druid_fhr,
    id_breakpoints_necromancer_ibs,
    id_breakpoints_necromancer_fcr,
    id_breakpoints_necromancer_fhr,
    id_breakpoints_paladin_ibs,
    id_breakpoints_paladin_fcr,
    id_breakpoints_paladin_fhr,
    id_breakpoints_sorceress_ibs,
    id_breakpoints_sorceress_fcr,
    id_breakpoints_sorceress_fhr,
    id_breakpoints_warlock_ibs,
    id_breakpoints_warlock_fcr,
    id_breakpoints_warlock_fhr,
    id_runewordlist_ancients_pledge = 160,
    id_runewordlist_authority,
    id_runewordlist_beast,
    id_runewordlist_black,
    id_runewordlist_bone,
    id_runewordlist_bramble,
    id_runewordlist_brand,
    id_runewordlist_breath_of_the_dying,
    id_runewordlist_bulwark,
    id_runewordlist_call_to_arms,
    id_runewordlist_chains_of_honor,
    id_runewordlist_coven,
    id_runewordlist_crescent_moon,
    id_runewordlist_cure,
    id_runewordlist_death,
    id_runewordlist_delirium,
    id_runewordlist_destruction,
    id_runewordlist_doom,
    id_runewordlist_dragon,
    id_runewordlist_dream,
    id_runewordlist_duress,
    id_runewordlist_edge,
    id_runewordlist_enigma,
    id_runewordlist_enlightenment,
    id_runewordlist_eternity,
    id_runewordlist_exile,
    id_runewordlist_faith,
    id_runewordlist_famine,
    id_runewordlist_flickering_flame,
    id_runewordlist_fortitude,
    id_runewordlist_fury,
    id_runewordlist_gloom,
    id_runewordlist_grief,
    id_runewordlist_ground,
    id_runewordlist_hand_of_justice,
    id_runewordlist_harmony,
    id_runewordlist_heart_of_the_oak,
    id_runewordlist_hearth,
    id_runewordlist_holy_hunder,
    id_runewordlist_honor,
    id_runewordlist_hysteria,
    id_runewordlist_ice,
    id_runewordlist_infinity,
    id_runewordlist_insight,
    id_runewordlist_kings_grace,
    id_runewordlist_kingslayer,
    id_runewordlist_last_wish,
    id_runewordlist_lawbringer,
    id_runewordlist_leaf,
    id_runewordlist_lionheart,
    id_runewordlist_lore,
    id_runewordlist_malice,
    id_runewordlist_mania,
    id_runewordlist_melody,
    id_runewordlist_memory,
    id_runewordlist_metamorphosis,
    id_runewordlist_mist,
    id_runewordlist_mosaic,
    id_runewordlist_myth,
    id_runewordlist_nadir,
    id_runewordlist_oath,
    id_runewordlist_obedience,
    id_runewordlist_obsession,
    id_runewordlist_passion,
    id_runewordlist_pattern,
    id_runewordlist_peace,
    id_runewordlist_phoenix,
    id_runewordlist_plague,
    id_runewordlist_pride,
    id_runewordlist_principle,
    id_runewordlist_prudence,
    id_runewordlist_radiance,
    id_runewordlist_rain,
    id_runewordlist_rhyme,
    id_runewordlist_ritual,
    id_runewordlist_rift,
    id_runewordlist_sanctuary,
    id_runewordlist_silence,
    id_runewordlist_smoke,
    id_runewordlist_spirit,
    id_runewordlist_splendor,
    id_runewordlist_stealth,
    id_runewordlist_steel,
    id_runewordlist_stone,
    id_runewordlist_strength,
    id_runewordlist_temper,
    id_runewordlist_treachery,
    id_runewordlist_unbending_will,
    id_runewordlist_venom,
    id_runewordlist_vigilance,
    id_runewordlist_voice_of_reason,
    id_runewordlist_void,
    id_runewordlist_wealth,
    id_runewordlist_white,
    id_runewordlist_wind,
    id_runewordlist_wisdom,
    id_runewordlist_wrath,
    id_runewordlist_zephyr

};


class MainFrame : public wxFrame{
public:
    wxCheckBox *cb_el, *cb_eld, *cb_tir, *cb_nef, *cb_eth, *cb_ith, *cb_tal,
    *cb_ral, *cb_ort, *cb_thul, *cb_amn, *cb_sol, *cb_shael, *cb_dol, *cb_hel,
    *cb_io, *cb_lum, *cb_ko, *cb_fal, *cb_lem, *cb_pul, *cb_um, *cb_mal,
    *cb_ist, *cb_gul, *cb_vex, *cb_ohm, *cb_lo, *cb_sur, *cb_ber, *cb_jah,
    *cb_cham, *cb_zod;

    set<wxCheckBox*> set_cb_pointers;

    MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

    void InvertRunes(wxCommandEvent &event);
    void ResetRunes(wxCommandEvent &event);
    void SortRunes(wxCommandEvent &event);
    void ShowRunewordStats(wxCommandEvent &event);
    void DeleteResultCheckboxContents();
    void ClearResultCheckboxSelections();
    void CalculateResults(wxCommandEvent &event);
    string GetRunewordText(string a);

    wxFont *my_font = new wxFont(16, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL,
        wxFONTWEIGHT_NORMAL);
    wxStaticText *static_results = new wxStaticText(this, wxID_ANY, "",
        wxPoint(1060, 16), wxSize(500, 500));
    wxListBox *result_listbox = new wxListBox(this, id_runeword_listbox,
        wxPoint(570, 40), wxSize(400, 400));


    wxArrayString choice_arr1;  // item type
    wxChoice *choice_1;

    wxArrayString choice_arr2;  // sockets
    wxChoice *choice_2;

    wxArrayString choice_arr3;  // max level req
    wxChoice *choice_3;



    wxButton *btn_sort;

    // its VERY IMPORTANT that the event table itself is defined in the cpp file, not here (you only declare it here)
    DECLARE_EVENT_TABLE()

private:
    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    // breakpoint event functions

    // amazon
    void OnBreakpointsAmazonIBS(wxCommandEvent &event);
    void OnBreakpointsAmazonFCR(wxCommandEvent &event);
    void OnBreakpointsAmazonFHR(wxCommandEvent &event);

    // assassin
    void OnBreakpointsAssassinIBS(wxCommandEvent &event);
    void OnBreakpointsAssassinFCR(wxCommandEvent &event);
    void OnBreakpointsAssassinFHR(wxCommandEvent &event);

    // barbarian
    void OnBreakpointsBarbarianIBS(wxCommandEvent &event);
    void OnBreakpointsBarbarianFCR(wxCommandEvent &event);
    void OnBreakpointsBarbarianFHR(wxCommandEvent &event);

    // druid
    void OnBreakpointsDruidIBS(wxCommandEvent &event);
    void OnBreakpointsDruidFCR(wxCommandEvent &event);
    void OnBreakpointsDruidFHR(wxCommandEvent &event);

    // necromancer
    void OnBreakpointsNecromancerIBS(wxCommandEvent &event);
    void OnBreakpointsNecromancerFCR(wxCommandEvent &event);
    void OnBreakpointsNecromancerFHR(wxCommandEvent &event);

    // paladin
    void OnBreakpointsPaladinIBS(wxCommandEvent &event);
    void OnBreakpointsPaladinFCR(wxCommandEvent &event);
    void OnBreakpointsPaladinFHR(wxCommandEvent &event);

    // sorceress
    void OnBreakpointsSorceressIBS(wxCommandEvent &event);
    void OnBreakpointsSorceressFCR(wxCommandEvent &event);
    void OnBreakpointsSorceressFHR(wxCommandEvent &event);

    // warlock
    void OnBreakpointsWarlockIBS(wxCommandEvent &event);
    void OnBreakpointsWarlockFCR(wxCommandEvent &event);
    void OnBreakpointsWarlockFHR(wxCommandEvent &event);

    // click event
    void OnRunewordListSelectionClick(wxCommandEvent &event);

};


#endif
