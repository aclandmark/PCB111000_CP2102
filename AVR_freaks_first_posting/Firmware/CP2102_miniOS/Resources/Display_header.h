



	//FOR CP2102 PCB111000
#define	seg_a 	PIN1_bm
#define	seg_b 	PIN4_bm
#define	seg_c 	PIN5_bm
#define	seg_d 	PIN2_bm
#define	seg_e 	PIN3_bm
#define	seg_f 	PIN1_bm
#define	seg_g 	PIN3_bm
#define	DP		PIN3_bm


#define	digit_0		PORTA.OUT |= PIN1_bm;
#define	digit_1		PORTC.OUT |= PIN2_bm;
#define	digit_2		PORTC.OUT |= PIN0_bm;
#define	digit_3		PORTB.OUT |= PIN0_bm;
#define	digit_4		PORTA.OUT |= PIN5_bm;
#define	digit_5		PORTB.OUT |= PIN4_bm;
#define	digit_6		PORTA.OUT |= PIN7_bm;
#define	digit_7		PORTA.OUT |= PIN6_bm;


//All ports are outputs
#define Set_display_ports \
PORTA.DIR |= (PIN1_bm | PIN3_bm | PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm);\
PORTB.DIR |= (PIN0_bm | PIN1_bm | PIN2_bm | PIN3_bm | PIN4_bm | PIN5_bm);\
PORTC.DIR |= (PIN0_bm | PIN1_bm | PIN2_bm | PIN3_bm);


//#define clear_digits Set all digits low
#define clear_digits \
PORTA.OUT &= (~(PIN1_bm | PIN5_bm | PIN6_bm | PIN7_bm));\
PORTB.OUT &= (~(PIN0_bm | PIN4_bm));\
PORTC.OUT &= (~(PIN0_bm | PIN2_bm));


//#define clear_display Set all segments high
#define clear_display \
PORTA.OUT |= (seg_b | seg_e);\
PORTB.OUT |= (seg_a | seg_c | seg_d | DP);\
PORTC.OUT |= (seg_f | seg_g);


#define clear_display_buffer	for(int m = 0; m<=14; m++)display_buffer[m] = 0;
#define clear_temp_buffer		for(int m = 0; m<=14; m++)temp_buffer[m] = 0;


#define one_U 	PORTA.OUT &= (~(seg_b));
#define ONE_U 	PORTC.OUT &= (~(seg_f));
#define one_L 	PORTB.OUT &= (~(seg_c));
#define ONE_L 	PORTA.OUT &= (~(seg_e));
#define ONE		PORTA.OUT &= (~(seg_e));																				PORTC.OUT &= (~(seg_f));

#define one 		PORTA.OUT &=(~(seg_b));						PORTB.OUT &= ~(seg_c);
#define two 		PORTA.OUT &= (~(seg_b | seg_e));			PORTB.OUT &= (~(seg_a | seg_d));						PORTC.OUT &= (~(seg_g));
#define three 		PORTA.OUT &=(~(seg_b));						PORTB.OUT &= (~(seg_a | seg_c | seg_d));				PORTC.OUT &= (~(seg_g));
#define four 		PORTA.OUT &= (~(seg_b));					PORTB.OUT &= (~(seg_c));								PORTC.OUT &= (~(seg_f | seg_g));
#define five 													PORTB.OUT &= (~(seg_a | seg_c | seg_d ));				PORTC.OUT &= (~(seg_f  | seg_g));
#define six 		PORTA.OUT &=(~(seg_e));						PORTB.OUT &= (~(seg_c | seg_d ));						PORTC.OUT &= (~(seg_f | seg_g));
#define seven 		PORTA.OUT &= (~(seg_b));					PORTB.OUT &= (~(seg_a | seg_c));
#define eight 		PORTA.OUT &= (~(seg_b | seg_e));			PORTB.OUT &= (~(seg_a | seg_c| seg_d));					PORTC.OUT &= (~(seg_f | seg_g));
#define nine		PORTA.OUT &= (~(seg_b));					PORTB.OUT &= (~(seg_a | seg_c));						PORTC.OUT &= (~( seg_f | seg_g));
#define zero		PORTA.OUT &= (~(seg_b  | seg_e));			PORTB.OUT &= (~(seg_a | seg_c | seg_d ));				PORTC.OUT &= (~( seg_f));
#define minus																											PORTC.OUT &= (~(seg_g));
#define exponent	PORTA.OUT &= ~(seg_e);						PORTB.OUT &= (~(seg_a | seg_d));						PORTC.OUT &= (~(seg_f | seg_g ));
#define underscore												PORTB.OUT &= (~(seg_d));


#define zero_point		zero;	PORTB.OUT &= ~DP;
#define one_point		one;	PORTB.OUT &= ~DP;
#define two_point		two; 	PORTB.OUT &= ~DP;
#define three_point		three; 	PORTB.OUT &= ~DP;
#define four_point		four; 	PORTB.OUT &= ~DP;
#define five_point		five; 	PORTB.OUT &= ~DP;
#define six_point		six; 	PORTB.OUT &= ~DP;
#define seven_point		seven; 	PORTB.OUT &= ~DP;
#define eight_point		eight; 	PORTB.OUT &= ~DP;
#define nine_point		nine; 	PORTB.OUT &= ~DP;
#define minus_point		minus;	PORTB.OUT &= ~DP;









//FP display
/**************************************************
#define	seg_a 	PIN5_bm
#define	seg_b 	PIN4_bm
#define	seg_c 	PIN1_bm
#define	seg_d 	PIN3_bm
#define	seg_e 	PIN2_bm
#define	seg_f 	PIN1_bm
#define	seg_g 	PIN0_bm
#define	DP		PIN2_bm


#define	digit_7		PORTA.OUT |= PIN1_bm;
#define	digit_6		PORTA.OUT |= PIN2_bm;
#define	digit_5		PORTA.OUT |= PIN3_bm;
#define	digit_4		PORTB.OUT |= PIN0_bm;
#define	digit_3		PORTA.OUT |= PIN4_bm;
#define	digit_2		PORTA.OUT |= PIN5_bm;
#define	digit_1		PORTA.OUT |= PIN6_bm;
#define	digit_0		PORTA.OUT |= PIN7_bm;


//All ports are outputs
#define Set_display_ports \
PORTA.DIR |= (PIN1_bm | PIN2_bm | PIN3_bm | PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm);\
PORTB.DIR |= (PIN0_bm | PIN1_bm | PIN2_bm | PIN3_bm | PIN4_bm | PIN5_bm);\
PORTC.DIR |= (PIN0_bm | PIN1_bm | PIN2_bm);


//#define clear_digits Set all digits low
#define clear_digits \
PORTA.OUT &= (~(PIN1_bm | PIN2_bm | PIN3_bm | PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm));\
PORTB.OUT &= (~(PIN0_bm));


//#define clear_display Set all segments high
#define clear_display \
PORTB.OUT |= (seg_a | seg_b | seg_c | seg_d | DP);\
PORTC.OUT |= (seg_e | seg_f | seg_g);


#define clear_display_buffer	for(int m = 0; m<=14; m++)display_buffer[m] = 0;
#define clear_temp_buffer		for(int m = 0; m<=14; m++)temp_buffer[m] = 0;




#define one_U 	PORTB.OUT &= ~(seg_b);
#define ONE_U 	PORTC.OUT &= ~(seg_f);
#define one_L 	PORTB.OUT &= ~(seg_c);
#define ONE_L 	PORTC.OUT &= ~(seg_e);
#define ONE		PORTC.OUT &= (~(seg_e | seg_f));

#define one 	PORTB.OUT &= ~(seg_b | seg_c);
#define two 	PORTB.OUT &= (~(seg_a | seg_b | seg_d));				PORTC.OUT &= (~(seg_e | seg_g));
#define three 	PORTB.OUT &= (~(seg_a | seg_b | seg_c | seg_d));		PORTC.OUT &= (~(seg_g));
#define four 	PORTB.OUT &= (~(seg_b | seg_c));						PORTC.OUT &= (~(seg_f | seg_g));
#define five 	PORTB.OUT &= (~(seg_a | seg_c | seg_d ));				PORTC.OUT &= (~(seg_f  | seg_g));
#define six 	PORTB.OUT &= (~(seg_c | seg_d ));						PORTC.OUT &= (~(seg_e | seg_f | seg_g));
#define seven 	PORTB.OUT &= (~(seg_a | seg_b | seg_c));
#define eight 	PORTB.OUT &= (~(seg_a | seg_b | seg_c| seg_d));			PORTC.OUT &= (~(seg_e  | seg_f | seg_g));
#define nine	PORTB.OUT &= (~(seg_a | seg_b | seg_c));				PORTC.OUT &= (~( seg_f | seg_g));
#define zero	PORTB.OUT &= (~(seg_a | seg_b | seg_c | seg_d ));		PORTC.OUT &= (~( seg_f  | seg_e  ));
#define minus															PORTC.OUT &= (~(seg_g));
#define exponent	PORTB.OUT &= (~(seg_a | seg_d));					PORTC.OUT &= (~(seg_e | seg_f | seg_g ));



#define zero_point		zero; PORTB.OUT &= ~DP;
#define one_point		one; PORTB.OUT &= ~DP;
#define two_point		two;  PORTB.OUT &= ~DP;
#define three_point		three;  PORTB.OUT &= ~DP;
#define four_point		four;  PORTB.OUT &= ~DP;
#define five_point		five;  PORTB.OUT &= ~DP;
#define six_point		six;  PORTB.OUT &= ~DP;
#define seven_point		seven;  PORTB.OUT &= ~DP;
#define eight_point		eight;  PORTB.OUT &= ~DP;
#define nine_point		nine;  PORTB.OUT &= ~DP;
#define minus_point		minus; PORTB.OUT &= ~DP;

************************************************************************/

