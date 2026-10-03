#include QMK_KEYBOARD_H

uint8_t selected_layout = 0;

void send_alt_shift_backspace(void) {
    register_code(KC_LSFT);
    register_code(KC_LALT);
    register_code(KC_BSPC);
    unregister_code(KC_BSPC);
    unregister_code(KC_LALT);
    unregister_code(KC_LSFT);
}

void send_ctrl_shift_b(void) {
    register_code(KC_LSFT);
    register_code(KC_LCTL);
    register_code(KC_B);
    unregister_code(KC_B);
    unregister_code(KC_LCTL);
    unregister_code(KC_LSFT);
}

void send_shift_alt_1(void) {
    register_code(KC_LSFT);
    register_code(KC_LALT);
    register_code(KC_1);
    unregister_code(KC_1);
    unregister_code(KC_LALT);
    unregister_code(KC_LSFT);
}

void send_shift_alt_0(void) {
    register_code(KC_LSFT);
    register_code(KC_LALT);
    register_code(KC_0);
    unregister_code(KC_0);
    unregister_code(KC_LALT);
    unregister_code(KC_LSFT);
}

enum custom_keycodes {
    IZH_LAT = SAFE_RANGE,
    IZH_RUS,  IZH_HASH, IZH_PIPE, IZH_QUES, IZH_CIRC, IZH_GRV,  IZH_AMPR, IZH_COLN,
    IZH_QUOT, IZH_DQT,  IZH_DLR,  IZH_SCLN, IZH_TILD, IZH_SLSH, IZH_AT,   IZH_LCBR, 
    IZH_RCBR, IZH_LT,   IZH_GT,   IZH_LBRC, IZH_RBRC, IZH_NUM,  IZH_LAQT, IZH_RAQT,
    IZH_LCQT, IZH_RCQT, IZH_DEG,  IZH_BYAT, IZH_SYAT, IZH_BFIT, IZH_SFIT, IZH_BIZH,
    IZH_SIZH, IZH_BI,   IZH_SI,   IZH_DASH, IZH_MINS, IZH_RUB,  IZH_COM,  IZH_PER,
    IZH_UP8,  IZH_DWN8, US_X1,    US_X2,    IZH_BILD, IZH_BACK, IZH_VER,
    IZH_YAT,  IZH_FITA, IZH_IZHC, IZH_IDEC,
    IZH_SOFT, IZH_SHA
};

#define CT_VER  IZH_VER
#define CT_BACK IZH_BACK
#define CT_BILD IZH_BILD
#define CT_CMNT IZH_CMNT
#define CT_LAT  IZH_LAT
#define CT_RUS  IZH_RUS
#define RUS_LT  LT(6, KC_F24)   /* tap: Russian layout, hold: old-orthography layer */
#define US_HASH IZH_HASH
#define US_PIPE IZH_PIPE
#define US_QUES IZH_QUES
#define US_CIRC IZH_CIRC
#define US_GRV  IZH_GRV
#define US_AMPR IZH_AMPR
#define US_COLN IZH_COLN
#define US_QUOT IZH_QUOT
#define US_DQT  IZH_DQT
#define US_DLR  IZH_DLR
#define US_SCLN IZH_SCLN
#define US_TILD IZH_TILD
#define US_SLSH IZH_SLSH
#define US_AT   IZH_AT
#define US_LCBR IZH_LCBR
#define US_RCBR IZH_RCBR
#define US_LT   IZH_LT
#define US_GT   IZH_GT
#define US_LBRC IZH_LBRC
#define US_RBRC IZH_RBRC
#define US_NUM  IZH_NUM
#define US_LAQT IZH_LAQT
#define US_RAQT IZH_RAQT
#define US_LCQT IZH_LCQT
#define US_RCQT IZH_RCQT
#define US_DEG  IZH_DEG
#define US_BYAT IZH_BYAT
#define US_SYAT IZH_SYAT
#define US_BFIT IZH_BFIT
#define US_SFIT IZH_SFIT
#define US_BIZH IZH_BIZH
#define US_SIZH IZH_SIZH
#define US_BI   IZH_BI
#define US_SI   IZH_SI
#define US_DASH IZH_DASH
#define US_MINS IZH_MINS
#define US_RUB  IZH_RUB
#define US_COM  IZH_COM
#define US_PER  IZH_PER



/* Send a WinCompose sequence: RAlt, then the code */
static void send_compose(const char *code) {
    SEND_STRING(SS_TAP(X_RALT));
    send_string(code);
}

/* Send upper- or lowercase letter depending on Shift; Shift is released while sending */
static void send_cased(const char *upper, const char *lower) {
    uint8_t mods      = get_mods();
    uint8_t weak_mods = get_weak_mods();
    bool    shifted   = (mods | weak_mods) & MOD_MASK_SHIFT;
    del_mods(MOD_MASK_SHIFT);
    del_weak_mods(MOD_MASK_SHIFT);
    send_keyboard_report();
    send_compose(shifted ? upper : lower);
    set_mods(mods);
    set_weak_mods(weak_mods);
    send_keyboard_report();
}

/* Rus key: nested press (hold Rus, tap letter) = layer; fast roll Rus -> letter = layout switch */
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    return keycode != RUS_LT;
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    return keycode == RUS_LT;
}

/* Instant double tap: first tap types the base letter at once,
 * a quick second tap erases it and types the alternate (ь -> ъ, ш -> щ).
 * A third quick tap starts over with the base letter. */
static uint16_t dt_last_key   = KC_NO;  /* custom key of the previous tap   */
static uint16_t dt_timer      = 0;      /* time of the previous tap         */
static bool     dt_converted  = false;  /* previous tap already gave ъ / щ  */
static uint16_t dt_registered[2] = {KC_NO, KC_NO}; /* code held per key, for release */

static void tap_backspace_without_shift(void) {
    uint8_t mods      = get_mods();
    uint8_t weak_mods = get_weak_mods();
    del_mods(MOD_MASK_SHIFT);
    del_weak_mods(MOD_MASK_SHIFT);
    send_keyboard_report();
    tap_code(KC_BSPC);
    set_mods(mods);
    set_weak_mods(weak_mods);
    send_keyboard_report();
}

static bool process_instant_double(uint16_t keycode, keyrecord_t *record,
                                   uint8_t idx, uint16_t base, uint16_t alt) {
    if (record->event.pressed) {
        bool quick = dt_last_key == keycode && !dt_converted &&
                     timer_elapsed(dt_timer) < TAPPING_TERM;
        if (quick) {
            tap_backspace_without_shift();
            dt_registered[idx] = alt;
            dt_converted       = true;
        } else {
            dt_registered[idx] = base;
            dt_converted       = false;
        }
        register_code(dt_registered[idx]);
        dt_last_key = keycode;
        dt_timer    = timer_read();
    } else {
        unregister_code(dt_registered[idx]);
        dt_registered[idx] = KC_NO;
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    /* any other key breaks the double-tap chain */
    if (record->event.pressed && keycode != IZH_SOFT && keycode != IZH_SHA) {
        dt_last_key = KC_NO;
    }

    switch (keycode) {
        case IZH_SOFT: /* ь, double: ъ */
            return process_instant_double(keycode, record, 0, KC_M, KC_RBRC);
        case IZH_SHA:  /* ш, double: щ */
            return process_instant_double(keycode, record, 1, KC_I, KC_O);

        case CT_BACK:
            if (record->event.pressed) {
                send_alt_shift_backspace();
                return false;
            }
            break;
        case CT_BILD:
            if (record->event.pressed) {
                send_ctrl_shift_b();
                return false;
            }
            break;
        case CT_LAT:
            if (record->event.pressed) {
                layer_move(0);
                send_shift_alt_0();
                selected_layout = 0;
                return false;
            }
            break;
        case CT_RUS:
            if (record->event.pressed) {
                layer_move(1);
                send_shift_alt_1();
                selected_layout = 1;
                return false;
            }
            break;
        case IZH_UP8:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_UP) SS_TAP(X_UP) SS_TAP(X_UP) SS_TAP(X_UP));
                SEND_STRING(SS_TAP(X_UP) SS_TAP(X_UP) SS_TAP(X_UP) SS_TAP(X_UP));
            }
            return false;
        case IZH_DWN8:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_DOWN) SS_TAP(X_DOWN) SS_TAP(X_DOWN) SS_TAP(X_DOWN));
                SEND_STRING(SS_TAP(X_DOWN) SS_TAP(X_DOWN) SS_TAP(X_DOWN) SS_TAP(X_DOWN));
            }
            return false;

        case US_X1: /*X#*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0023"); } return false;
        case US_X2: /*X;*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0059"); } return false;

        case RUS_LT:
            if (record->tap.count) {
                if (record->event.pressed) {
                    layer_move(1);
                    send_shift_alt_1();
                    selected_layout = 1;
                }
                return false;
            }
            return true;

        case IZH_YAT:  /* Ѣ ѣ */
            if (record->event.pressed) { send_cased("1122", "1123"); } return false;
        case IZH_FITA: /* Ѳ ѳ */
            if (record->event.pressed) { send_cased("1138", "1139"); } return false;
        case IZH_IZHC: /* Ѵ ѵ */
            if (record->event.pressed) { send_cased("1140", "1141"); } return false;
        case IZH_IDEC: /* І і */
            if (record->event.pressed) { send_cased("1030", "1110"); } return false;

        case IZH_VER: /* Firmware version */
            if (record->event.pressed) { SEND_STRING("1.7"); } return false;

        case US_HASH: /*#*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0023"); } return false;
        case US_PIPE: /*|*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0124"); } return false;
        case US_QUES: /*?*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0063"); } return false;
        case US_CIRC: /*^*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0094"); } return false;
        case US_GRV:  /*`*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0096"); } return false;
        case US_AMPR: /*&*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0038"); } return false;
        case US_COLN: /*:*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0058"); } return false;
        case US_QUOT: /*'*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0039"); } return false;
        case US_DQT:  /*"*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0034"); } return false;
        case US_DLR:  /*$*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0036"); } return false;
        case US_SCLN: /*;*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0059"); } return false;
        case US_TILD: /*~*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0126"); } return false;
        case US_SLSH: /*/*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0047"); } return false;
        case US_AT:   /*@*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0064"); } return false;
        case US_LCBR: /*{*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0123"); } return false;
        case US_RCBR: /*}*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0125"); } return false;
        case US_LT:   /*<*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0060"); } return false;
        case US_GT:   /*>*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0062"); } return false;
        case US_LBRC: /*[*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0091"); } return false;
        case US_RBRC: /*]*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0093"); } return false;
        case US_NUM:  /*№*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("8470"); } return false;
        case US_LAQT: /*«*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0171"); } return false;
        case US_RAQT: /*»*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0187"); } return false;
        case US_LCQT: /*„*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("8222"); } return false;
        case US_RCQT: /*“*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("8220"); } return false;
        case US_DEG:  /*°*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0176"); } return false;
        case US_BYAT: /*Ѣ*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("1122"); } return false;
        case US_SYAT: /*ѣ*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("1123"); } return false;
        case US_BFIT: /*Ѳ*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("1138"); } return false;
        case US_SFIT: /*ѳ*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("1139"); } return false;
        case US_BIZH: /*Ѵ*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("1140"); } return false;
        case US_SIZH: /*ѵ*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("1141"); } return false;
        case US_BI:   /*І*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("1030"); } return false;
        case US_SI:   /*і*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("1110"); } return false;
        case US_DASH: /*—*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("8212"); } return false;
        case US_MINS: /*−*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("8722"); } return false;
        case US_RUB:  /*₽*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("8381"); } return false;
        case US_COM:  /*,*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0044"); } return false;
        case US_PER:  /*.*/
            if (record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0046"); } return false;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Base layer
     * ┌─────┬─────┬─────┬─────┬─────┬─────┐  ┌─────┬─────┬─────┬─────┬─────┬─────┐
     * │     │  Q  │  W  │  E  │  R  │  T  │  │  Y  │  U  │  I  │  O  │     │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┤  ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │ Lat │  A  │  S  │  D  │  F  │  G  │  │  H  │  J  │  K  │  L  │  P  │ Rus │
     * ├─────┼─────┼─────┼─────┼─────┼─────┤  ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │  /  │  Z  │  X  │  C  │  V  │  B  │  │  N  │  M  │  ,  │  .  │     │  /  │
     * └─────┴─────┴─────┼─────┼─────┼─────┤  ├─────┼─────┼─────┼─────┴─────┴─────┘
     *                   │ Esc │Bkspc│Enter│  │     │Space│Shift│
     *                   │ Ctrl│ Fun │ Num │  │ Sym │ Nav │     │
     *                   └─────┴─────┴─────┘  └─────┴─────┴─────┘
     */
    [0] = LAYOUT_ortho_4x16(
        KC_NO,   KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,     KC_Y,  KC_U,  KC_I,    KC_O,    KC_NO,  KC_NO,
        CT_LAT,  KC_A,  KC_S,  KC_D,  KC_F,  KC_G,     KC_H,  KC_J,  KC_K,    KC_L,    KC_P,   RUS_LT,
        KC_NO,   KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,     KC_N,  KC_M,  KC_COMM, KC_DOT,  KC_NO,  KC_NO,
     LCTL_T(KC_ESC), LT(4, KC_BSPC), LT(3, KC_ENT),    MO(2), LT(5, KC_SPC), KC_RSFT
    ),

    /* Rus base layer
     * ┌─────┬─────┬─────┬─────┬─────┬─────┐  ┌─────┬─────┬─────┬─────┬─────┬─────┐
     * │  Э  │  Й  │  Ц  │  У  │  К  │  Е  │  │  Н  │  Г  │ Ш Щ │  Б  │  З  │  Х  │
     * │  '  │  Q  │  W  │  E  │  R  │  T  │  │  Y  │  U  │  I  │  ,  │  P  │  [  │
     * ├─────┼─────┼─────┼─────┼─────┼─────┤  ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │ Lat │  Ф  │  Ы  │  В  │  А  │  П  │  │  Р  │  О  │  Л  │  Д  │  Ж  │ Rus │
     * │     │  A  │  S  │  D  │  F  │  G  │  │  H  │  J  │  K  │  L  │  ;  │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┤  ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │  Ё  │  Я  │  Ч  │  С  │  М  │  И  │  │  Т  │ Ь Ъ │  ,  │  .  │  Ю  │  /  │
     * │     │  Z  │  X  │  C  │  V  │  B  │  │  N  │  M  │  ?  │  /  │  .  │     │
     * └─────┴─────┴─────┼─────┼─────┼─────┤  ├─────┼─────┼─────┼─────┴─────┴─────┘
     *                   │ Esc │Bkspc│Enter│  │     │Space│Shift│
     *                   │ Ctrl│ Fun │ Num │  │ Sym │ Nav │     │
     *                   └─────┴─────┴─────┘  └─────┴─────┴─────┘
     */
    [1] = LAYOUT_ortho_4x16(
        KC_QUOT,  KC_Q,  KC_W,      KC_E,  KC_R,  KC_T,       KC_Y,  KC_U,      IZH_SHA  , KC_COMM, KC_P,    KC_LBRC,
        CT_LAT,   KC_A,  KC_S,      KC_D,  KC_F,  KC_G,       KC_H,  KC_J,      KC_K,      KC_L,    KC_SCLN, RUS_LT,
        KC_GRV,   KC_Z,  KC_X,      KC_C,  KC_V,  KC_B,       KC_N,  IZH_SOFT , KC_QUES,   KC_SLSH, KC_DOT,  KC_NO,
        LCTL_T(KC_ESC),  LT(4, KC_BSPC),   LT(3, KC_ENT),     MO(2), LT(5, KC_SPC),        KC_RSFT
    ),

    /* Symbols layer
     * ┌─────┬─────┬─────┬─────┬─────┬─────┐  ┌─────┬─────┬─────┬─────┬─────┬─────┐
     * │     │  !  │  #  │  ?  │  %  │  _  │  │  @  │  (  │  *  │  )  │  ^  │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┤  ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │     │  :  │  +  │  '  │  "  │  [  │  │  >  │  =  │  -  │  $  │  ;  │  `  │
     * ├─────┼─────┼─────┼─────┼─────┼─────┤  ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │     │  №  │  /  │  |  │  \  │  ]  │  │  <  │  {  │  &  │  }  │  ~  │     │
     * └─────┴─────┴─────┼─────┼─────┼─────┤  ├─────┼─────┼─────┼─────┴─────┴─────┘
     *                   │ Esc │Bkspc│Enter│  │_Sym_│Space│     │
     *                   └─────┴─────┴─────┘  └─────┴─────┴─────┘
     */
    [2] = LAYOUT_ortho_4x16(
        US_X1,   KC_EXLM,  US_HASH,  US_QUES,  KC_PERC,  KC_UNDS,      US_AT, KC_LPRN, KC_ASTR, KC_RPRN, US_CIRC, KC_NO,    
        US_X2,   US_COLN,  KC_PLUS,  US_QUOT,  US_DQT,   US_LBRC,      US_GT, KC_EQL,  KC_MINS, US_DLR,  US_SCLN, US_GRV,
        KC_NO,   US_NUM,   KC_BSLS,  US_PIPE,  US_SLSH,  US_RBRC,      US_LT, US_LCBR, US_AMPR, US_RCBR, US_TILD, KC_NO,
                                       KC_ESC, KC_BSPC,  KC_ENT,       KC_NO, KC_SPC,  KC_NO
    ),

    /* Nums layer
     * ┌─────┬─────┬─────┬─────┬─────┬─────┐  ┌─────┬─────┬─────┬─────┬─────┬─────┐
     * │     │  8  │  7  │  6  │  5  │  9  │  │  9  │  5  │  6  │  7  │  8  │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┤  ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │  /  │  4  │  3  │  2  │  1  │  0  │  │  0  │  1  │  2  │  3  │  4  │  /  │
     * ├─────┼─────┼─────┼─────┼─────┼─────┤  ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │  /  │     │  .  │  ,  │     │     │  │     │     │  ,  │  .  │     │  /  │
     * └─────┴─────┴─────┼─────┼─────┼─────┤  ├─────┼─────┼─────┼─────┴─────┴─────┘
     *                   │ Esc │Bkspc│_Num_│  │     │Space│     │
     *                   └─────┴─────┴─────┘  └─────┴─────┴─────┘
     */
    [3] = LAYOUT_ortho_4x16(
        KC_NO,   KC_8,   KC_7,    KC_6,    KC_5,   KC_9,       KC_9,    KC_5,   KC_6,    KC_7,    KC_8,   KC_NO,
        KC_NO,   KC_4,   KC_3,    KC_2,    KC_1,   KC_0,       KC_0,    KC_1,   KC_2,    KC_3,    KC_4,   KC_NO,
        KC_NO,   KC_NO,  US_PER,  US_COM,  KC_NO,  KC_NO,      KC_NO,   KC_NO,  US_COM,  US_PER,  KC_NO,  KC_NO,
                                KC_ESC,  KC_BSPC,  KC_NO,      KC_NO,   KC_SPC, KC_NO
    ),

    /* Fn layer
     * ┌─────┬─────┬─────┬─────┬─────┬─────┐  ┌─────┬─────┬─────┬─────┬─────┬─────┐
     * │ F5  │ Redo│ Cut │Paste│ Copy│ Undo│  │     │CpsLk│PrScr│     │     │ Ver │
     * ├─────┼─────┼─────┼─────┼─────┼─────┤  ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │Build│ Win │ Alt │ Ctrl│Shift│ CMNT│  │     │Shift│ Ctrl│ Alt │ Win │  /  │
     * ├─────┼─────┼─────┼─────┼─────┼─────┤  ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │  /  │ Win1│ Win2│ Win3│ Win4│S-F12│  │ F5  │ F8  │ F9  │ F10 │ F11 │  /  │
     * └─────┴─────┴─────┼─────┼─────┼─────┤  ├─────┼─────┼─────┼─────┴─────┴─────┘
     *                   │ Esc │_Fun_│Enter│  │     │Space│     │
     *                   └─────┴─────┴─────┘  └─────┴─────┴─────┘
     */
    [4] = LAYOUT_ortho_4x16(
        KC_F5,   C(KC_Y),  C(KC_X),  C(KC_V),  C(KC_C),  C(KC_Z),      KC_NO,   KC_CAPS,  KC_PSCR,  KC_NO,    KC_NO,    IZH_VER,
        CT_BILD, KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT,  C(KC_SLSH),   KC_NO,   KC_RSFT,  KC_RCTL,  KC_LALT,  KC_RGUI,  KC_NO,
        KC_NO,   G(KC_1),  G(KC_2),  G(KC_3),  G(KC_4),  S(KC_F12),    KC_F5,   KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_NO,
                                     KC_ESC,   KC_NO,    KC_ENT,       KC_NO,   KC_SPC,   KC_NO
    ),

    /* Nav layer
     * ┌─────┬─────┬─────┬─────┬─────┬─────┬┬─────┬─────┬─────┬─────┬─────┬─────┐
     * │     │ Redo│ Cut │Paste│ Copy│ Undo││Up8  │ Home│ Up  │ End │     │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │Build│ Win │ Alt │ Ctrl│Shift│ CMNT││Down8│ Left│ Down│Right│ Tab │  /  │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │  /  │ Win1│ Win2│ Win3│ Win4│ Win5││ Del │Ctl-L│Ctl-R│ Back│     │  /  │
     * └─────┴─────┴─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┴─────┴─────┘
     *                   │ Esc │Bkspc│Enter││     │_Nav_│     │
     *                   └─────┴─────┴─────┴┴─────┴─────┴─────┘
     */
    [5] = LAYOUT_ortho_4x16(
        KC_NO,   C(KC_Y),  C(KC_X),  C(KC_V),  C(KC_C),  C(KC_Z),         IZH_UP8,   KC_HOME,     KC_UP,       KC_END,   KC_NO,   KC_NO,
        CT_BILD, KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT,  C(KC_SLSH),      IZH_DWN8,  KC_LEFT,     KC_DOWN,     KC_RGHT,  KC_TAB,  KC_NO,
        KC_NO,   G(KC_1),  G(KC_2),  G(KC_3),  G(KC_4),  G(KC_5),         KC_DEL,    C(KC_LEFT),  C(KC_RGHT),  CT_BACK,  KC_NO,   KC_NO,
                                     KC_ESC,   KC_BSPC,  KC_ENT,          KC_NO,     KC_NO,       KC_NO
    ),

    /* Old orthography layer (hold Rus)
     * ┌─────┬─────┬─────┬─────┬─────┬─────┐  ┌─────┬─────┬─────┬─────┬─────┬─────┐
     * │     │  „  │  “  │  «  │  »  │ ѣ Ѣ │  │     │     │     │     │     │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┤  ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │     │ ѳ Ѳ │     │  °  │  ₽  │     │  │     │     │     │     │     │_Rus_│
     * ├─────┼─────┼─────┼─────┼─────┼─────┤  ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │     │     │  —  │  −  │ ѵ Ѵ │ і І │  │     │     │     │     │     │     │
     * └─────┴─────┴─────┼─────┼─────┼─────┤  ├─────┼─────┼─────┼─────┴─────┴─────┘
     *                   │  ▽  │  ▽  │  ▽  │  │  ▽  │  ▽  │Shift│
     *                   └─────┴─────┴─────┘  └─────┴─────┴─────┘
     * Uppercase letters: hold Shift (right thumb)
     */
    [6] = LAYOUT_ortho_4x16(
        KC_NO,   US_LCQT,  US_RCQT,  US_LAQT,  US_RAQT,  IZH_YAT,      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   IZH_FITA, KC_NO,    US_DEG,   US_RUB,   KC_NO,        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS,
        KC_NO,   KC_NO,    US_DASH,  US_MINS,  IZH_IZHC, IZH_IDEC,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                                     KC_TRNS,  KC_TRNS,  KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS
    )
};
