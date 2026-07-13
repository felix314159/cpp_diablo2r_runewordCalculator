#include "MainApp.h"


bool MainApp::OnInit(){
    // define window size
    MainFrame *frame = new MainFrame("D2R Runeword Calculator",
                        wxPoint(1, 1), wxSize(1800, 600));
    frame->SetTitle(wxT("D2R Runeword Calculator"));
    frame->Show(true);
    SetTopWindow(frame);

    populate_runewords(runewords);  // fill runeword vector with runeword objects

    return true;
}

wxIMPLEMENT_APP(MainApp);
