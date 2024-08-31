#include QMK_KEYBOARD_H

enum custom_keycodes {
    IZH_LAT = SAFE_RANGE,
    IZH_RUS
};

enum unicode_symbols {
    IZH_HASH, IZH_PIPE, IZH_QUES, IZH_CIRC, IZH_GRV,  IZH_AMPR, IZH_COLN, IZH_QUOT, 
    IZH_DQT,  IZH_DLR,  IZH_SCLN, IZH_TILD, IZH_SLSH, IZH_AT,   IZH_LCBR, IZH_RCBR,
    IZH_LT,   IZH_GT,   IZH_LBRC, IZH_RBRC, IZH_NUM,  IZH_LAQT, IZH_RAQT, IZH_LCQT,
    IZH_RCQT, IZH_DEG,  IZH_BYAT, IZH_SYAT, IZH_BFIT, IZH_SFIT, IZH_BIZH, IZH_SIZH,
    IZH_BI,   IZH_SI,   IZH_DASH, IZH_MINS, IZH_RUB
};

const uint32_t unicode_map[] PROGMEM = {
    [IZH_HASH] = 0x0023, /*#*/    [IZH_PIPE] = 0x007C, /*|*/    [IZH_QUES] = 0x003F, /*?*/
    [IZH_CIRC] = 0x005E, /*^*/    [IZH_GRV]  = 0x0060, /*`*/    [IZH_AMPR] = 0x0026, /*&*/
    [IZH_COLN] = 0x003A, /*:*/    [IZH_QUOT] = 0x0027, /*'*/    [IZH_DQT]  = 0x0022, /*"*/
    [IZH_DLR]  = 0x0024, /*$*/    [IZH_SCLN] = 0x003B, /*;*/    [IZH_TILD] = 0x007E, /*~*/
    [IZH_SLSH] = 0x002F, /*/*/    [IZH_AT]   = 0x0040, /*@*/    [IZH_LCBR] = 0x007B, /*{*/
    [IZH_RCBR] = 0x007D, /*}*/    [IZH_LT]   = 0x003C, /*<*/    [IZH_GT]   = 0x003E, /*>*/
    [IZH_LBRC] = 0x005B, /*[*/    [IZH_RBRC] = 0x005D, /*]*/    [IZH_NUM]  = 0x2116, /*№*/
    [IZH_LAQT] = 0x0171, /*«*/    [IZH_RAQT] = 0x0187, /*»*/    [IZH_LCQT] = 0x201E, /*„*/
    [IZH_RCQT] = 0x201C, /*“*/    [IZH_DEG]  = 0x00B0, /*°*/    [IZH_BYAT] = 0x0462, /*Ѣ*/
    [IZH_SYAT] = 0x0463, /*ѣ*/    [IZH_BFIT] = 0x0472, /*Ѳ*/    [IZH_SFIT] = 0x0473, /*ѳ*/
    [IZH_BIZH] = 0x0474, /*Ѵ*/    [IZH_SIZH] = 0x0475, /*ѵ*/    [IZH_BI]   = 0x0178, /*І*/
    [IZH_SI]   = 0x0179, /*і*/    [IZH_DASH] = 0x2014, /*—*/    [IZH_MINS] = 0x2212, /*−*/
    [IZH_RUB]  = 0x20BD  /*₽*/
};

#define US_HASH RALT(UM(IZH_HASH))
#define US_PIPE RALT(UM(IZH_PIPE))
#define US_QUES RALT(UM(IZH_QUES))
#define US_CIRC RALT(UM(IZH_CIRC))
#define US_GRV  RALT(UM(IZH_GRV))
#define US_AMPR RALT(UM(IZH_AMPR))
#define US_COLN RALT(UM(IZH_COLN))
#define US_QUOT RALT(UM(IZH_QUOT))
#define US_DQT  RALT(UM(IZH_DQT))
#define US_DLR  RALT(UM(IZH_DLR))
#define US_SCLN RALT(UM(IZH_SCLN))
#define US_TILD RALT(UM(IZH_TILD))
#define US_SLSH RALT(UM(IZH_SLSH))
#define US_AT   RALT(UM(IZH_AT))
#define US_LCBR RALT(UM(IZH_LCBR))
#define US_RCBR RALT(UM(IZH_RCBR))
#define US_LT   RALT(UM(IZH_LT))
#define US_GT   RALT(UM(IZH_GT))
#define US_LBRC RALT(UM(IZH_LBRC))
#define US_RBRC RALT(UM(IZH_RBRC))
#define US_NUM  RALT(UM(IZH_NUM))
#define US_LAQT RALT(UM(IZH_LAQT))
#define US_RAQT RALT(UM(IZH_RAQT))
#define US_LCQT RALT(UM(IZH_LCQT))
#define US_RCQT RALT(UM(IZH_RCQT))
#define US_DEG  RALT(UM(IZH_DEG))
#define US_BYAT RALT(UM(IZH_BYAT))
#define US_SYAT RALT(UM(IZH_SYAT))
#define US_BFIT RALT(UM(IZH_BFIT))
#define US_SFIT RALT(UM(IZH_SFIT))
#define US_BIZH RALT(UM(IZH_BIZH))
#define US_SIZH RALT(UM(IZH_SIZH))
#define US_BI   RALT(UM(IZH_BI))
#define US_SI   RALT(UM(IZH_SI))
#define US_DASH RALT(UM(IZH_DASH))
#define US_MINS RALT(UM(IZH_MINS))
#define US_RUB  RALT(UM(IZH_RUB))

#define CT_LAT RSFT_T(IZH_LAT)
#define CT_RUS RSFT_T(IZH_RUS)


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CT_LAT:
            if (record->tap.count && record->event.pressed) {
                layer_move(0);
                SEND_STRING(SS_LCTL("0"));
                return false;
            }
            break;
        case CT_RUS:
            if (record->tap.count && record->event.pressed) {
                layer_move(1);
                SEND_STRING(SS_LCTL("1"));
                return false;
            }
            break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Base layer
     * ┌─────┬─────┬─────┬─────┬─────┬─────┬┬─────┬─────┬─────┬─────┬─────┬─────┐
     * │     │  Q  │  W  │  E  │  R  │  T  ││  Y  │  U  │  I  │  O  │     │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │ Esc │  A  │  S  │  D  │  F  │  G  ││  H  │  J  │  K  │  L  │  P  │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │     │  Z  │  X  │  C  │  V  │  B  ││  N  │  M  │  ,  │  .  │     │     │
     * └─────┴─────┴─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┴─────┴─────┘
     *                   │ Lat │Bkspc│     ││Enter│Space│ Rus │
     *                   │Shift│ Num │ Fun ││ Sym │ Nav │Shift│
     *                   └─────┴─────┴─────┴┴─────┴─────┴─────┘
     */
    [0] = LAYOUT_ortho_4x16(
        KC_NO,   KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,     KC_Y,  KC_U,  KC_I,    KC_O,    KC_NO,  KC_NO,
        KC_ESC,  KC_A,  KC_S,  KC_D,  KC_F,  KC_G,     KC_H,  KC_J,  KC_K,    KC_L,    KC_P,   KC_NO,
        KC_NO,   KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,     KC_N,  KC_M,  KC_COMM, KC_DOT,  KC_NO,  KC_NO,
                    CT_LAT, LT(3, KC_BSPC),  MO(4),    LT(2, KC_ENT), LT(5, KC_SPC),   CT_RUS
    ),

    /* Rus base layer
     * ┌─────┬─────┬─────┬─────┬─────┬─────┬┬─────┬─────┬─────┬─────┬─────┬─────┐
     * │  Ё  │  Й  │  Ц  │  У  │  К  │  Е  ││  Н  │  Г  │  Ш  │  Б  │  З  │  Х  │
     * │  `  │  Q  │  W  │  E  │  R  │  T  ││  Y  │  U  │  I  │  ,  │  P  │  [  │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │ Esc │  Ф  │  Ы  │  В  │  А  │  П  ││  Р  │  О  │  Л  │  Д  │  Ж  │  Э  │
     * │     │  A  │  S  │  D  │  F  │  G  ││  H  │  J  │  K  │  L  │  ;  │  '  │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │  Ъ  │  Я  │  Ч  │  С  │  М  │  И  ││  Т  │  Ь  │  ,  │  .  │  Ю  │  Щ  │
     * │  ]  │  Z  │  X  │  C  │  V  │  B  ││  N  │  M  │  ?  │  /  │  .  │  O  │
     * └─────┴─────┴─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┴─────┴─────┘
     *                   │ Lat │Bkspc│     ││Enter│Space│ Rus │
     *                   │Shift│ Num │ Fun ││ Sym │ Nav │Shift│
     *                   └─────┴─────┴─────┴┴─────┴─────┴─────┘
     */
    [1] = LAYOUT_ortho_4x16(
        KC_GRV,   KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,     KC_Y,  KC_U,  KC_I,    KC_COMM,  KC_P,     KC_LBRC,
        KC_ESC,   KC_A,  KC_S,  KC_D,  KC_F,  KC_G,     KC_H,  KC_J,  KC_K,    KC_L,     KC_SCLN,  KC_QUOT,
        KC_RBRC,  KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,     KC_N,  KC_M,  KC_QUES, KC_SLSH,  KC_DOT,   KC_O,
                    CT_LAT, LT(3, KC_BSPC),  MO(4),    LT(2, KC_ENT), LT(5, KC_SPC),   CT_RUS
    ),

    /* Symbols layer 
     * ┌─────┬─────┬─────┬─────┬─────┬─────┬┬─────┬─────┬─────┬─────┬─────┬─────┐
     * │     │  !  │  #  │  ?  │  %  │     ││     │  ^  │  *  │  `  │  &  │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │ Esc │  :  │  +  │  '  │  "  │  _  ││  |  │  =  │  -  │  $  │  ;  │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │     │     │  №  │  ~  │  \  │     ││     │  /  │  @  │     │     │     │
     * └─────┴─────┴─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┴─────┴─────┘
     *                   │     │Bkspc│Enter││_Sym_│     │     │
     *                   └─────┴─────┴─────┴┴─────┴─────┴─────┘
     */
    [2] = LAYOUT_ortho_4x16(
        KC_NO,   KC_EXLM,  US_HASH,  US_QUES,  KC_PERC,  KC_NO,        KC_NO,    US_CIRC,  KC_ASTR,  US_GRV,  US_AMPR,  KC_NO,    
        KC_ESC,  US_COLN,  KC_PLUS,  US_QUOT,  US_DQT,   KC_UNDS,      US_PIPE,  KC_EQL,   KC_MINS,  US_DLR,  US_SCLN,  KC_NO,
        KC_NO,   KC_NO,    US_NUM,   US_TILD,  KC_BSLS,  KC_NO,        KC_NO,    US_SLSH,  US_AT,    KC_NO,   KC_NO,    KC_NO,
                                     KC_NO,    KC_BSPC,  KC_ENT,       KC_NO,    KC_NO,    KC_NO
    ),

    /* Nums layer
     * ┌─────┬─────┬─────┬─────┬─────┬─────┬┬─────┬─────┬─────┬─────┬─────┬─────┐
     * │     │     │  7  │  8  │  9  │     ││     │  (  │  {  │  <  │  [  │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │ Esc │  0  │  4  │  5  │  6  │     ││     │Shift│ Ctrl│ Alt │ Win │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │     │     │  1  │  2  │  3  │     ││     │  )  │  }  │  >  │  ]  │     │
     * └─────┴─────┴─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┴─────┴─────┘
     *                   │     │_Num_│     ││Space│     │     │
     *                   └─────┴─────┴─────┴┴─────┴─────┴─────┘
     */
    [3] = LAYOUT_ortho_4x16(
        KC_NO,   KC_NO,  KC_7,  KC_8,   KC_9,   KC_NO,      KC_NO,   KC_LPRN,  KC_LCBR,  KC_LT,    KC_LBRC,   KC_NO,
        KC_ESC,  KC_0,   KC_4,  KC_5,   KC_6,   KC_NO,      KC_NO,   KC_RSFT,  KC_RCTL,  KC_LALT,  KC_RGUI,   KC_NO,
        KC_NO,   KC_NO,  KC_1,  KC_2,   KC_3,   KC_NO,      KC_NO,   KC_RPRN,  KC_RCBR,  KC_GT,    KC_RBRC,   KC_NO,
                                KC_NO,  KC_NO,  KC_NO,      KC_SPC,  KC_NO,    KC_NO
    ),

    /* Fn layer Copy│Paste│ Cut Undo│
     * ┌─────┬─────┬─────┬─────┬─────┬─────┬┬─────┬─────┬─────┬─────┬─────┬─────┐
     * │     │ Undo│ Copy│Paste│ Cut │ Redo││     │CpsLk│PrScr│     │     │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │ Esc │ Win │ Alt │ Ctrl│Shift│     ││     │Shift│ Ctrl│ Alt │ Win │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │     │ F11 │ F10 │ F9  │ F8  │ F5  ││     │     │     │     │     │     │
     * └─────┴─────┴─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┴─────┴─────┘
     *                   │_Fun_│     │     ││Space│     │     │
     *                   └─────┴─────┴─────┴┴─────┴─────┴─────┘
     */
    [4] = LAYOUT_ortho_4x16(
        KC_NO,   KC_UNDO,  KC_CUT,   KC_PSTE,  KC_COPY,  C(KC_Y),      KC_NO,   KC_CAPS,  KC_PSCR,  KC_NO,    KC_NO,    KC_NO,
        KC_ESC,  KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT,  KC_NO,        KC_NO,   KC_RSFT,  KC_RCTL,  KC_LALT,  KC_RGUI,  KC_NO,
        KC_NO,   KC_F11,   KC_F10,   KC_F9,    KC_F8,    KC_F5,        KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
                                     KC_NO,    KC_NO,    KC_NO,        KC_SPC,  KC_NO,    KC_NO
    ),

    /* Nav layer
     * ┌─────┬─────┬─────┬─────┬─────┬─────┬┬─────┬─────┬─────┬─────┬─────┬─────┐
     * │     │ Undo│ Copy│Paste│ Cut │ Redo││MsUp │ Home│ Up  │ End │     │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │ Esc │ Win │ Alt │ Ctrl│Shift│Ctl-/││MsDwn│ Left│ Down│Right│ Tab │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │     │     │     │     │     │MsLCk││ Del │Ctl-L│Ctl-R│     │     │     │
     * └─────┴─────┴─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┴─────┴─────┘
     *                   │     │Bkspc│Enter││     │_Nav_│     │
     *                   └─────┴─────┴─────┴┴─────┴─────┴─────┘
     */
    [5] = LAYOUT_ortho_4x16(
        KC_NO,   KC_UNDO,  KC_CUT,   KC_PSTE,  KC_COPY,  C(KC_Y),         KC_WH_U,  KC_HOME,     KC_UP,       KC_END,   KC_NO,   KC_NO,
        KC_ESC,  KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT,  C(KC_SLSH),      KC_WH_D,  KC_LEFT,     KC_DOWN,     KC_RGHT,  KC_TAB,  KC_NO,
        KC_NO,   G(KC_4),  G(KC_3),  G(KC_2),  G(KC_1),  KC_BTN1,         KC_DEL,   C(KC_LEFT),  C(KC_RGHT),  KC_NO,    KC_NO,   KC_NO,
                                     KC_NO,    KC_BSPC,  KC_ENT,          KC_NO,    KC_NO,       KC_NO
    )
};
