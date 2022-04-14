#include <QDebug>

/*
// this is the wrong way to use booleans (code is ambiguous)
namespace {
  
  void setupPlot(bool displayAsYearOnYear) {
    // Setup a plot with one axis from say Jan 2020 to Dec 2021
    // or with one axis from Jan to Dec showing two plots one for 2020 and one for 2021
    qDebug().noquote() << "Step 2: Plotting"
                       << (displayAsYearOnYear ? "Year on Year" : "Continuously");
  }

}

void go()
{
  setupPlot(false);
}
*/

// the correct way is to use enums!

namespace {

enum class PlotType {YearOnYear, Continuously};

  void setupPlot(PlotType type ) {
    // Setup a plot with one axis from say Jan 2020 to Dec 2021
    // or with one axis from Jan to Dec showing two plots one for 2020 and one for 2021
    qDebug().noquote() << "Step 2: Plotting"
                       << (type == PlotType::YearOnYear ? "Year on Year" : "Continuously");
  }

}


  void go2()
{
  setupPlot(PlotType::YearOnYear);
}
