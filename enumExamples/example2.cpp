#include <QDebug>

/*
// this is the wrong way to use booleans (code is ambiguous)
namespace {

  void party(bool makeIce, bool brewCoffee, bool openBeers) 
  {
    qDebug().noquote() << "Step 4: Lets Party, here are the jobs to do:\n"
                       << "Make Ice: " << (makeIce ? "Yes" : "No") << "\n"
                       << "Brew Coffee: " << (brewCoffee ? "Yes" : "No") << "\n"
                       << "Open Beers: " << (openBeers ? "Yes" : "No");

  }
}

void go()
{
  party(false, false, false);
}
*/

// the correct way is to use enums!

namespace {
  enum class PartyOption { BoringParty = 0x0, MakeIce = 0x1, BrewCoffee = 0x2, OpenBeers = 0x4 };

  Q_DECLARE_FLAGS(PartyOptions, PartyOption)
  Q_DECLARE_OPERATORS_FOR_FLAGS(PartyOptions)
  
  void party(PartyOptions options)
  {
    qDebug().noquote() << "Step 4: Lets Party, here are the jobs to do:\n"
                       << "Make Ice: " << (options & PartyOption::MakeIce ? "Yes" : "No") << "\n"
                       << "Brew Coffee: " << (options & PartyOption::BrewCoffee ? "Yes" : "No") << "\n"
                       << "Open Beers: " << (options & PartyOption::OpenBeers  ? "Yes" : "No");
  }
}

void go2()
{
  party(PartyOption::BrewCoffee | PartyOption::OpenBeers);
}
