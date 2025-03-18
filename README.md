# Thereminimum
A tiny digital theremin I created as a test of the Seeed XIAO thumb-sized microcontrollers and a laser range-finder, as well as battery use and my soldering. 

Hardware required: 
<ul>
  <li>Seeed Studios XIAO ESP32-S3 micricintroller (or equivalent)</li>
  <li>Adafruit VL53L1X laser ranging breakout board (or equivalent)</li>
  <li>Adafruit PS1240 piezo buzzer (or equivalent)</li>
</ul>
All wired up as follows:

<img src=thereminimum.jpg width=500>
(the Fritzing file is <A href=thereminimum.fzz>here</A>a>.)

Soldered together, it should look something like this:

<img src=thereminimum_top.jpeg width=500>

Since Seeed Studio have somehow managed to cram in battery management to their tiny board, I also attached a small rechargeable battery (3.7V 100mAh 601120) and an on/off dip switch to the bottom of the board for stand-alone operation:

<img src=thereminimum_bottom.jpeg width=500>

A simple code to make it play is <A href=thereminimum.ino>here</a>; you will also need to download the <A href=note_frequencies.h>header file</a> that defines note frequencies.

If all goes well, it should end up sounding something <A href=thereminimum.mov>like this</a>.
