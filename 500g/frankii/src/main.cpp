#include <Arduino.h>
#include "../include/FrankiAction.h"
#include "../include/FrankiState.h"


FrankiAction frankiAction = FrankiAction();
FrankiState frankiState = FrankiState();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  frankiState.updateState();
  frankiAction.sampleFloor();

}



void loop() {

  frankiState.updateState();

  bool startModuleActivated = frankiState.startModuleIsActive();
  bool leftDetected = frankiState.leftIRDetected();
  bool midLeftDetected = frankiState.midLeftIRDetected();
  bool midDetected = frankiState.midIRDetected();
  bool midRightDetected = frankiState.midRightIRDetected();
  bool rightDetected = frankiState.rightIRDetected();
  bool isLineDetected = frankiState.isAtBounds();


  if (startModuleActivated) {

    if (midDetected && !midLeftDetected && !midRightDetected) {

      if (isLineDetected) { frankiAction.boundaryDetectedManuever(); } 
      else { frankiAction.fullFowards(); }

    } else if (midDetected && midLeftDetected && midRightDetected) {

        if (isLineDetected) { frankiAction.boundaryDetectedManuever(); } 
        else { frankiAction.fullFowards(); }

      } else if (midDetected && midLeftDetected && !midRightDetected) {

        if (isLineDetected) { frankiAction.boundaryDetectedManuever(); } 
        else { frankiAction.slightLeft(); }

      } else if (midDetected && !midLeftDetected && midRightDetected) {

        if (isLineDetected) { frankiAction.boundaryDetectedManuever(); } 
        else { frankiAction.slightRight(); }

      } else if (!midDetected && midLeftDetected && !midRightDetected) {

        if (isLineDetected) { frankiAction.boundaryDetectedManuever(); } 
        else { frankiAction.left(); }

      } else if (!midDetected && !midLeftDetected && midRightDetected) {

        if (isLineDetected) { frankiAction.boundaryDetectedManuever(); } 
        else { frankiAction.right(); }

      } else if (rightDetected) {

        if (isLineDetected) { frankiAction.boundaryDetectedManuever(); } 
        else { frankiAction.sharpRight(); }

      } else if (leftDetected) {

        if (isLineDetected) { frankiAction.boundaryDetectedManuever(); } 
        else { frankiAction.sharpLeft(); }

      } else {

        frankiAction.search();

      }


  } else { // startmodule activation status brackets
    frankiAction.stop();
  }
}
