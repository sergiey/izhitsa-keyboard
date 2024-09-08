#include QMK_KEYBOARD_H

enum {
    TD_BRC = 0,
    TD_CBR,
    TD_TBR,
    TD_PRN,
    TD_ER,
    TD_SH,
    TD_YO
};

void td_brc(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        SEND_STRING(SS_TAP(X_RALT));
        SEND_STRING("0091");
        return;
    }
    if (state->count >= 1) {
        SEND_STRING(SS_TAP(X_RALT));
        SEND_STRING("0093");
        return;
    }
}

void td_cbr(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        SEND_STRING(SS_TAP(X_RALT));
        SEND_STRING("0123");
        return;
    }
    if (state->count >= 1) {
        SEND_STRING(SS_TAP(X_RALT));
        SEND_STRING("0125");
        return;
    }
}

void td_tbr(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        SEND_STRING(SS_TAP(X_RALT));
        SEND_STRING("0060");
        return;
    }
    if (state->count >= 1) {
        SEND_STRING(SS_TAP(X_RALT));
        SEND_STRING("0062");
        return;
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_BRC] = ACTION_TAP_DANCE_FN(td_brc),
    [TD_CBR] = ACTION_TAP_DANCE_FN(td_cbr),
    [TD_TBR] = ACTION_TAP_DANCE_FN(td_tbr),
    [TD_PRN] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_RPRN),
    [TD_ER]  = ACTION_TAP_DANCE_DOUBLE(KC_M, KC_RBRC),
    [TD_SH]  = ACTION_TAP_DANCE_DOUBLE(KC_I, KC_O),
    [TD_YO]  = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_GRV)
};

enum custom_keycodes {
    IZH_LAT = SAFE_RANGE,
    IZH_RUS,  IZH_HASH, IZH_PIPE, IZH_QUES, IZH_CIRC, IZH_GRV,  IZH_AMPR, IZH_COLN,
    IZH_QUOT, IZH_DQT,  IZH_DLR,  IZH_SCLN, IZH_TILD, IZH_SLSH, IZH_AT,   IZH_LCBR, 
    IZH_RCBR, IZH_LT,   IZH_GT,   IZH_LBRC, IZH_RBRC, IZH_NUM,  IZH_LAQT, IZH_RAQT,
    IZH_LCQT, IZH_RCQT, IZH_DEG,  IZH_BYAT, IZH_SYAT, IZH_BFIT, IZH_SFIT, IZH_BIZH,
    IZH_SIZH, IZH_BI,   IZH_SI,   IZH_DASH, IZH_MINS, IZH_RUB  
};

#define US_HASH RSFT_T(IZH_HASH)
#define US_PIPE RSFT_T(IZH_PIPE)
#define US_QUES RSFT_T(IZH_QUES)
#define US_CIRC RSFT_T(IZH_CIRC)
#define US_GRV  RSFT_T(IZH_GRV)
#define US_AMPR RSFT_T(IZH_AMPR)
#define US_COLN RSFT_T(IZH_COLN)
#define US_QUOT RSFT_T(IZH_QUOT)
#define US_DQT  RSFT_T(IZH_DQT)
#define US_DLR  RSFT_T(IZH_DLR)
#define US_SCLN RSFT_T(IZH_SCLN)
#define US_TILD RSFT_T(IZH_TILD)
#define US_SLSH RSFT_T(IZH_SLSH)
#define US_AT   RSFT_T(IZH_AT)
#define US_LCBR RSFT_T(IZH_LCBR)
#define US_RCBR RSFT_T(IZH_RCBR)
#define US_LT   RSFT_T(IZH_LT)
#define US_GT   RSFT_T(IZH_GT)
#define US_LBRC RSFT_T(IZH_LBRC)
#define US_RBRC RSFT_T(IZH_RBRC)
#define US_NUM  RSFT_T(IZH_NUM)
#define US_LAQT RSFT_T(IZH_LAQT)
#define US_RAQT RSFT_T(IZH_RAQT)
#define US_LCQT RSFT_T(IZH_LCQT)
#define US_RCQT RSFT_T(IZH_RCQT)
#define US_DEG  RSFT_T(IZH_DEG)
#define US_BYAT RSFT_T(IZH_BYAT)
#define US_SYAT RSFT_T(IZH_SYAT)
#define US_BFIT RSFT_T(IZH_BFIT)
#define US_SFIT RSFT_T(IZH_SFIT)
#define US_BIZH RSFT_T(IZH_BIZH)
#define US_SIZH RSFT_T(IZH_SIZH)
#define US_BI   RSFT_T(IZH_BI)
#define US_SI   RSFT_T(IZH_SI)
#define US_DASH RSFT_T(IZH_DASH)
#define US_MINS RSFT_T(IZH_MINS)
#define US_RUB  RSFT_T(IZH_RUB)
#define CT_LAT LCTL_T(IZH_LAT)
#define CT_RUS RSFT_T(IZH_RUS)

uint8_t selected_layout = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CT_LAT:
            if (record->tap.count && record->event.pressed) {
                layer_move(0);
                SEND_STRING(SS_LCTL("0"));
                selected_layout = 0;
            }
            return false;
        case CT_RUS:
            if (record->tap.count && record->event.pressed) {
                layer_move(1);
                SEND_STRING(SS_LCTL("1"));
                selected_layout = 1;
            }
            return false;
        case US_HASH: /*#*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0023"); } return false;
        case US_PIPE: /*|*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0124"); } return false;
        case US_QUES: /*?*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0063"); } return false;
        case US_CIRC: /*^*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0094"); } return false;
        case US_GRV:  /*`*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0096"); } return false;
        case US_AMPR: /*&*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0038"); } return false;
        case US_COLN: /*:*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0058"); } return false;
        case US_QUOT: /*'*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0039"); } return false;
        case US_DQT:  /*"*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0034"); } return false;
        case US_DLR:  /*$*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0036"); } return false;
        case US_SCLN: /*;*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0059"); } return false;
        case US_TILD: /*~*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0126"); } return false;
        case US_SLSH: /*/*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0047"); } return false;
        case US_AT:   /*@*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0064"); } return false;
        case US_LCBR: /*{*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0123"); } return false;
        case US_RCBR: /*}*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0125"); } return false;
        case US_LT:   /*<*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0060"); } return false;
        case US_GT:   /*>*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0062"); } return false;
        case US_LBRC: /*[*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0091"); } return false;
        case US_RBRC: /*]*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0093"); } return false;
        case US_NUM:  /*№*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("8470"); } return false;
        case US_LAQT: /*«*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0369"); } return false;
        case US_RAQT: /*»*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0391"); } return false;
        case US_LCQT: /*„*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("8222"); } return false;
        case US_RCQT: /*“*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("8220"); } return false;
        case US_DEG:  /*°*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0176"); } return false;
        case US_BYAT: /*Ѣ*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("1122"); } return false;
        case US_SYAT: /*ѣ*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("1123"); } return false;
        case US_BFIT: /*Ѳ*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("1138"); } return false;
        case US_SFIT: /*ѳ*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("1139"); } return false;
        case US_BIZH: /*Ѵ*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("1140"); } return false;
        case US_SIZH: /*ѵ*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("1141"); } return false;
        case US_BI:   /*І*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0376"); } return false;
        case US_SI:   /*і*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("0377"); } return false;
        case US_DASH: /*—*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("8212"); } return false;
        case US_MINS: /*−*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("8722"); } return false;
        case US_RUB:  /*₽*/
            if (record->tap.count && record->event.pressed) { SEND_STRING(SS_TAP(X_RALT)); SEND_STRING("8381"); } return false;
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
     *                   │ Lat │Bkspc│ Esc ││Enter│Space│ Rus │
     *                   │ Ctrl│ Fun │ Num ││ Sym │ Nav │Shift│
     *                   └─────┴─────┴─────┴┴─────┴─────┴─────┘
     */
    [0] = LAYOUT_ortho_4x16(
        KC_NO,   KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,     KC_Y,  KC_U,  KC_I,    KC_O,    KC_NO,  KC_NO,
        KC_ESC,  KC_A,  KC_S,  KC_D,  KC_F,  KC_G,     KC_H,  KC_J,  KC_K,    KC_L,    KC_P,   KC_NO,
        KC_NO,   KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,     KC_N,  KC_M,  KC_COMM, KC_DOT,  KC_NO,  KC_NO,
           CT_LAT, LT(4, KC_BSPC),  LT(3, KC_ESC),     LT(2, KC_ENT), LT(5, KC_SPC),   CT_RUS
    ),

    /* Rus base layer
     * ┌─────┬─────┬─────┬─────┬─────┬─────┬┬─────┬─────┬─────┬─────┬─────┬─────┐
     * │  Ё  │ Й Ё │  Ц  │  У  │  К  │  Е  ││  Н  │  Г  │ Ш Щ │  Б  │  З  │  Х  │
     * │  `  │  Q  │  W  │  E  │  R  │  T  ││  Y  │  U  │  I  │  ,  │  P  │  [  │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │ Esc │  Ф  │  Ы  │  В  │  А  │  П  ││  Р  │  О  │  Л  │  Д  │  Ж  │  Э  │
     * │     │  A  │  S  │  D  │  F  │  G  ││  H  │  J  │  K  │  L  │  ;  │  '  │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │  Ъ  │  Я  │  Ч  │  С  │  М  │  И  ││  Т  │ Ь Ъ │  ,  │  .  │  Ю  │  Щ  │
     * │  ]  │  Z  │  X  │  C  │  V  │  B  ││  N  │  M  │  ?  │  /  │  .  │  O  │
     * └─────┴─────┴─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┴─────┴─────┘
     *                   │ Lat │Bkspc│ Esc ││Enter│Space│ Rus │
     *                   │ Ctrl│ Fun │ Num ││ Sym │ Nav │Shift│
     *                   └─────┴─────┴─────┴┴─────┴─────┴─────┘
     */
    [1] = LAYOUT_ortho_4x16(
        KC_GRV,   TD(TD_YO),  KC_W,  KC_E,  KC_R,  KC_T,     KC_Y,  KC_U,       TD(TD_SH),  KC_COMM,  KC_P,     KC_LBRC,
        KC_ESC,   KC_A,  KC_S,  KC_D,  KC_F,  KC_G,          KC_H,  KC_J,       KC_K,       KC_L,     KC_SCLN,  KC_QUOT,
        KC_RBRC,  KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,          KC_N,  TD(TD_ER),  KC_QUES,    KC_SLSH,  KC_DOT,   KC_O,
            CT_LAT, LT(4, KC_BSPC),  LT(3, KC_ESC),          LT(2, KC_ENT), LT(5, KC_SPC),   CT_RUS
    ),

    /* Symbols layer 
     * ┌─────┬─────┬─────┬─────┬─────┬─────┬┬─────┬─────┬─────┬─────┬─────┬─────┐
     * │     │  !  │  #  │  ?  │  %  │  _  ││  |  │  ^  │  *  │  `  │  &  │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │ Esc │  :  │  +  │  '  │  "  │ [ ] ││ ( ) │  =  │  -  │  $  │  ;  │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │     │     │  №  │  ~  │  \  │  @  ││  /  │ { } │ < > │     │     │     │
     * └─────┴─────┴─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┴─────┴─────┘
     *                   │ Ctrl│Bkspc│Enter││_Sym_│     │     │
     *                   └─────┴─────┴─────┴┴─────┴─────┴─────┘
     */
    [2] = LAYOUT_ortho_4x16(
        KC_NO,   KC_EXLM,  US_HASH,  US_QUES,  KC_PERC,  KC_UNDS,      KC_PIPE,    US_CIRC,    KC_ASTR,    US_GRV,  US_AMPR,  KC_NO,    
        KC_ESC,  US_COLN,  KC_PLUS,  US_QUOT,  US_DQT,   TD(TD_BRC),   TD(TD_PRN), KC_EQL,     KC_MINS,    US_DLR,  US_SCLN,  KC_NO,
        KC_NO,   KC_NO,    US_NUM,   US_TILD,  KC_BSLS,  KC_AT,        KC_SLSH,    TD(TD_CBR), TD(TD_TBR), KC_NO,   KC_NO,    KC_NO,
                                     KC_LCTL,  KC_BSPC,  KC_ENT,       KC_NO,      KC_NO,      KC_NO
    ),

    /* Nums layer
     * ┌─────┬─────┬─────┬─────┬─────┬─────┬┬─────┬─────┬─────┬─────┬─────┬─────┐
     * │     │  8  │  7  │  6  │  5  │  9  ││  9  │  5  │  6  │  7  │     │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │ Esc │  4  │  3  │  2  │  1  │  0  ││  0  │  1  │  2  │  3  │  4  │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │     │     │     │     │     │     ││     │     │     │     │     │     │
     * └─────┴─────┴─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┴─────┴─────┘
     *                   │     │     │_Num_││Enter│Space│Shift│
     *                   └─────┴─────┴─────┴┴─────┴─────┴─────┘
     */
    [3] = LAYOUT_ortho_4x16(
        KC_NO,   KC_8,   KC_7,   KC_6,   KC_5,   KC_9,       KC_9,    KC_5,   KC_6,   KC_7,   KC_8,   KC_NO,
        KC_ESC,  KC_4,   KC_3,   KC_2,   KC_1,   KC_0,       KC_0,    KC_1,   KC_2,   KC_3,   KC_4,   KC_NO,
        KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,      KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
                                 KC_NO,  KC_NO,  KC_NO,      KC_ENT,  KC_SPC, KC_RSFT
    ),

    /* Fn layer
     * ┌─────┬─────┬─────┬─────┬─────┬─────┬┬─────┬─────┬─────┬─────┬─────┬─────┐
     * │     │ Redo│ Cut │Paste│ Copy│ Undo││     │CpsLk│PrScr│     │     │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │ Esc │ Win │ Alt │ Ctrl│Shift│Ctl-/││     │Shift│ Ctrl│ Alt │ Win │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │     │ F11 │ F10 │ F9  │ F8  │ F5  ││     │     │     │     │     │     │
     * └─────┴─────┴─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┴─────┴─────┘
     *                   │     │_Fun_│     ││Enter│Space│Shift│
     *                   └─────┴─────┴─────┴┴─────┴─────┴─────┘
     */
    [4] = LAYOUT_ortho_4x16(
        KC_NO,   C(KC_Y),  C(KC_X),  C(KC_V),  C(KC_C),  C(KC_Z),      KC_NO,   KC_CAPS,  KC_PSCR,  KC_NO,    KC_NO,    KC_NO,
        KC_ESC,  KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT,  C(KC_SLSH),   KC_NO,   KC_RSFT,  KC_RCTL,  KC_LALT,  KC_RGUI,  KC_NO,
        KC_NO,   KC_F11,   KC_F10,   KC_F9,    KC_F8,    KC_F5,        KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
                                     KC_NO,    KC_NO,    KC_NO,        KC_ENT,  KC_SPC,   KC_RSFT
    ),

    /* Nav layer
     * ┌─────┬─────┬─────┬─────┬─────┬─────┬┬─────┬─────┬─────┬─────┬─────┬─────┐
     * │     │ Redo│ Cut │Paste│ Copy│ Undo││MsUp │ Home│ Up  │ End │     │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │ Esc │ Win │ Alt │ Ctrl│Shift│Ctl-/││MsDwn│ Left│ Down│Right│ Tab │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │ Win5│ Win4│ Win3│ Win2│ Win1│MsLCk││ Del │Ctl-L│Ctl-R│     │     │     │
     * └─────┴─────┴─────┼─────┼─────┼─────┼┼─────┼─────┼─────┼─────┴─────┴─────┘
     *                   │ Ctrl│Bkspc│Enter││     │_Nav_│     │
     *                   └─────┴─────┴─────┴┴─────┴─────┴─────┘
     */
    [5] = LAYOUT_ortho_4x16(
        KC_NO,   C(KC_Y),  C(KC_X),  C(KC_V),  C(KC_C),  C(KC_Z),         KC_WH_U,  KC_HOME,     KC_UP,       KC_END,   KC_NO,   KC_NO,
        KC_ESC,  KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT,  C(KC_SLSH),      KC_WH_D,  KC_LEFT,     KC_DOWN,     KC_RGHT,  KC_TAB,  KC_NO,
        G(KC_5), G(KC_4),  G(KC_3),  G(KC_2),  G(KC_1),  KC_BTN1,         KC_DEL,   C(KC_LEFT),  C(KC_RGHT),  KC_NO,    KC_NO,   KC_NO,
                                     KC_LCTL,  KC_BSPC,  KC_ENT,          KC_NO,    KC_NO,       KC_NO
    )
};
