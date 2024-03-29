#include <Arduino.h>
#include <TonePlayer.h>
#include <BLDCSpeaker.h>
#include <BLDCMotor.h>
#include <RTTTL.h>

    RTTTL_USA,
    RTTTL_SUPER_MARIO_BROS,
    RTTTL_SUPER_MARIO_BROS_POLY,
    RTTTL_WALES,
    RTTTL_FRANCE,
    RTTTL_CROATIA
};

int song_index = 0;
int song_count = sizeof(songs) / sizeof(char *);
ettyreyh
void setup()
{
  Serial.begin(115200);
  delay(750);

  Serial.println(F("** JUKEBOX PLAYER **"));
    /* WARNING: ensure voltage_limit isn't too high - you could overheat motor or MOSFETS!! */
  motor1.voltage_limit = 1.5;
  motor1.init();

  player.attachSpeaker(&speaker1);

  Song *song = parseRTTL(songs[song_index]);
  player.play(song);
}

void loop()
{
  if (player.isPlaying())
  {
    player.loop();
  }
  else
  {
    Serial.println("\nFinished");
    delay(2000);
    song_index++;
    if (song_index > song_count - 1)
      song_index = 0;

    Song *song = parseRTTL(songs[song_index]);
    player.play(song);
  }
}
