/*
  Define your palette and add to palettes list that is at the bottom.
  Its first 5 palettes is default in FastLED library.
  I advice you define at most 10 default palettes.
  Otherwise you need to modify Android app and recieving code in the Arduino. 
*/

DEFINE_GRADIENT_PALETTE(spellbound_p)
{
    0, 232,235, 40,
   12, 157,248, 46,
   25, 100,246, 51,
   45,  53,250, 33,
   63,  18,237, 53,
   81,  11,211,162,
   94,  18,147,214,
  101,  43,124,237,
  112,  49, 75,247,
  127,  49, 75,247,
  140,  92,107,247,
  150, 120,127,250,
  163, 130,138,252,
  173, 144,131,252,
  186, 148,112,252,
  196, 144, 37,176,
  211, 113, 18, 87,
  221, 163, 33, 53,
  234, 255,101, 78,
  247, 229,235, 46,
  255, 229,235, 46
};

DEFINE_GRADIENT_PALETTE(cloud_p)
{
    0, 247,149, 91,
  127, 208, 32, 71,
  255,  42, 79,188
};

DEFINE_GRADIENT_PALETTE(fireandice_p)
{
    0,  80,  2,  1,
   51, 206, 15,  1,
  101, 242, 34,  1,
  153,  16, 67,128,
  204,   2, 21, 69,
  255,   1,  2,  4
};

DEFINE_GRADIENT_PALETTE(bhw1_05_p)
{
    0,   1,221, 53,
  255,  73,  3,178
};

DEFINE_GRADIENT_PALETTE(bhw1_06_p)
{
    0, 184,  1,128,
  160,   1,193,182,
  219, 153,227,190,
  255, 255,255,255
};

CRGBPalette16 palettes[] = {RainbowColors_p, LavaColors_p, ForestColors_p, OceanColors_p, PartyColors_p,
                            spellbound_p, cloud_p, fireandice_p, bhw1_05_p, bhw1_06_p};
