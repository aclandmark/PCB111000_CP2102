<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.5.2">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting keepoldvectorfont="yes"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="6" fill="9" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="88" name="SimResults" color="9" fill="1" visible="yes" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="3_My_prog">
<packages>
<package name="CA_DUAL_LED">
<pad name="1" x="0" y="2.54" drill="0.9"/>
<pad name="2" x="0" y="0" drill="0.9"/>
<pad name="3" x="0" y="-2.54" drill="0.9"/>
<text x="1.27" y="3.175" size="1.27" layer="21">&gt;NAME</text>
<circle x="0" y="0" radius="3.175" width="0.127" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="CA_DUAL_LED">
<polygon width="0.254" layer="94">
<vertex x="0" y="0.762"/>
<vertex x="-0.762" y="1.524"/>
<vertex x="0.762" y="1.524"/>
</polygon>
<wire x1="-0.762" y1="0.508" x2="0" y2="0.508" width="0.254" layer="94"/>
<wire x1="0" y1="0.508" x2="0.762" y2="0.508" width="0.254" layer="94"/>
<wire x1="-0.762" y1="-0.508" x2="0" y2="-0.508" width="0.254" layer="94"/>
<polygon width="0.254" layer="94">
<vertex x="0" y="-0.762"/>
<vertex x="0.762" y="-1.524"/>
<vertex x="-0.762" y="-1.524"/>
</polygon>
<wire x1="0" y1="-0.508" x2="0.762" y2="-0.508" width="0.254" layer="94"/>
<wire x1="0" y1="0.508" x2="0" y2="-0.508" width="0.254" layer="94"/>
<pin name="3" x="0" y="-3.81" visible="off" length="short" rot="R90"/>
<pin name="1" x="0" y="3.81" visible="off" length="short" rot="R270"/>
<pin name="2" x="2.54" y="0" visible="off" length="short" rot="R180"/>
<text x="0.762" y="2.286" size="1.778" layer="94">&gt;NAME</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="LED" prefix="LED" uservalue="yes">
<description>RS228-5770</description>
<gates>
<gate name="G$1" symbol="CA_DUAL_LED" x="-10.16" y="12.7"/>
</gates>
<devices>
<device name="" package="CA_DUAL_LED">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="1_Home_library">
<packages>
<package name="1206@1">
<wire x1="1.6" y1="-0.8" x2="1.6" y2="0.8" width="0.127" layer="21"/>
<wire x1="1.6" y1="0.8" x2="-1.6" y2="0.8" width="0.127" layer="21"/>
<wire x1="-1.6" y1="0.8" x2="-1.6" y2="-0.8" width="0.127" layer="21"/>
<wire x1="-1.6" y1="-0.8" x2="1.6" y2="-0.8" width="0.127" layer="21"/>
<text x="-3.1" y="1.55" size="1.27" layer="27">&gt;VALUE</text>
<smd name="P$1" x="-1.75" y="0" dx="2.2" dy="2" layer="1" rot="R180"/>
<smd name="P$2" x="1.7" y="0" dx="2.2" dy="2" layer="1" rot="R180"/>
<text x="-2.286" y="0.508" size="1.27" layer="21">+</text>
<text x="-2.54" y="-2.54" size="1.27" layer="25">&gt;NAME</text>
</package>
<package name="SM_NO_PUSH_BUTTON">
<description>RE 51-0709</description>
<wire x1="0" y1="0" x2="0" y2="3" width="0.127" layer="21"/>
<wire x1="0" y1="3" x2="6" y2="3" width="0.127" layer="21"/>
<wire x1="6" y1="3" x2="6" y2="0" width="0.127" layer="21"/>
<wire x1="6" y1="0" x2="0" y2="0" width="0.127" layer="21"/>
<smd name="P$1" x="-2" y="1.5" dx="3.3" dy="2" layer="1"/>
<smd name="P$2" x="8" y="1.5" dx="3.5" dy="2" layer="1"/>
<text x="0" y="3.5" size="1.27" layer="25">&gt;NAME</text>
<text x="0" y="-1.5" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="DIL28-3">
<description>&lt;B&gt;Dual In Line&lt;/B&gt; 0.3 inch</description>
<wire x1="-18.542" y1="-0.635" x2="-18.542" y2="-2.794" width="0.1524" layer="21"/>
<wire x1="-18.542" y1="0.635" x2="-18.542" y2="-0.635" width="0.1524" layer="21" curve="-180"/>
<wire x1="-18.542" y1="-2.794" x2="18.542" y2="-2.794" width="0.1524" layer="21"/>
<wire x1="-18.542" y1="2.794" x2="-18.542" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-18.542" y1="2.794" x2="18.542" y2="2.794" width="0.1524" layer="21"/>
<wire x1="18.542" y1="2.794" x2="18.542" y2="-2.794" width="0.1524" layer="21"/>
<pad name="1" x="-16.51" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="2" x="-13.97" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="3" x="-11.43" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="4" x="-8.89" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="5" x="-6.35" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="6" x="-3.81" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="7" x="-1.27" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="8" x="1.27" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="9" x="3.81" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="10" x="6.35" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="11" x="8.89" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="12" x="11.43" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="13" x="13.97" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="14" x="16.51" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="15" x="16.51" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="16" x="13.97" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="17" x="11.43" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="18" x="8.89" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="19" x="6.35" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="20" x="3.81" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="21" x="1.27" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="22" x="-1.27" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="23" x="-3.81" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="24" x="-6.35" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="25" x="-8.89" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="26" x="-11.43" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="27" x="-13.97" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="28" x="-16.51" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<text x="-19.2024" y="-2.54" size="1.778" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="-15.875" y="-0.635" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="CAP">
<rectangle x1="-2.54" y1="-1.905" x2="-1.27" y2="1.905" layer="94"/>
<rectangle x1="1.27" y1="-1.905" x2="2.54" y2="1.905" layer="94"/>
<pin name="1" x="-5.08" y="0" visible="off" length="short"/>
<pin name="2" x="5.08" y="0" visible="off" length="short" rot="R180"/>
<text x="-1.27" y="-3.81" size="1.27" layer="96">&gt;VALUE</text>
<text x="-3.556" y="0.254" size="1.27" layer="94">+</text>
<text x="-2.54" y="2.54" size="1.778" layer="95">&gt;NAME</text>
</symbol>
<symbol name="RES">
<wire x1="-2.54" y1="0.762" x2="2.54" y2="0.762" width="0.254" layer="94"/>
<wire x1="2.54" y1="0.762" x2="2.54" y2="-0.762" width="0.254" layer="94"/>
<wire x1="2.54" y1="-0.762" x2="-2.54" y2="-0.762" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-0.762" x2="-2.54" y2="0.762" width="0.254" layer="94"/>
<text x="3.302" y="0.508" size="1.778" layer="94">&gt;VALUE</text>
<text x="3.302" y="-2.286" size="1.778" layer="94">&gt;NAME</text>
<pin name="P$1" x="-5.08" y="0" visible="off" length="short"/>
<pin name="P$2" x="5.08" y="0" visible="off" length="short" rot="R180"/>
</symbol>
<symbol name="SM_NO_PUSH_BUTTON">
<description>RE 51-0709</description>
<pin name="1" x="-2.54" y="0" visible="off" length="short"/>
<pin name="2" x="10.16" y="0" visible="off" length="short" rot="R180"/>
<circle x="0.635" y="0" radius="0.898025" width="0.254" layer="94"/>
<circle x="7.62" y="0" radius="0.898025" width="0.254" layer="94"/>
<wire x1="0.635" y1="0" x2="7.62" y2="1.27" width="0.254" layer="94"/>
</symbol>
<symbol name="23-I/O-2">
<wire x1="-17.78" y1="30.48" x2="20.32" y2="30.48" width="0.254" layer="94"/>
<wire x1="20.32" y1="30.48" x2="20.32" y2="-33.02" width="0.254" layer="94"/>
<wire x1="20.32" y1="-33.02" x2="-17.78" y2="-33.02" width="0.254" layer="94"/>
<wire x1="-17.78" y1="-33.02" x2="-17.78" y2="30.48" width="0.254" layer="94"/>
<text x="-17.78" y="-35.56" size="1.778" layer="95">&gt;NAME</text>
<text x="-17.78" y="31.75" size="1.778" layer="96">&gt;VALUE</text>
<pin name="PB5(SCK)" x="25.4" y="-30.48" length="middle" rot="R180"/>
<pin name="PB7(XTAL2/TOSC2)" x="-22.86" y="5.08" length="middle"/>
<pin name="PB6(XTAL1/TOSC1)" x="-22.86" y="10.16" length="middle"/>
<pin name="GND@1" x="-22.86" y="-2.54" length="middle" direction="pwr"/>
<pin name="VCC@1" x="-22.86" y="-7.62" length="middle" direction="pwr"/>
<pin name="GND" x="-22.86" y="22.86" length="middle" direction="pwr"/>
<pin name="AREF" x="-22.86" y="20.32" length="middle" direction="pas"/>
<pin name="AVCC" x="-22.86" y="17.78" length="middle" direction="pwr"/>
<pin name="PB4(MISO)" x="25.4" y="-27.94" length="middle" rot="R180"/>
<pin name="PB3(MOSI/OC2)" x="25.4" y="-25.4" length="middle" rot="R180"/>
<pin name="PB2(SS/OC1B)" x="25.4" y="-22.86" length="middle" rot="R180"/>
<pin name="PB1(OC1A)" x="25.4" y="-20.32" length="middle" rot="R180"/>
<pin name="PB0(ICP)" x="25.4" y="-17.78" length="middle" rot="R180"/>
<pin name="PD7(AIN1)" x="25.4" y="-12.7" length="middle" rot="R180"/>
<pin name="PD6(AIN0)" x="25.4" y="-10.16" length="middle" rot="R180"/>
<pin name="PD5(T1)" x="25.4" y="-7.62" length="middle" rot="R180"/>
<pin name="PD4(XCK/T0)" x="25.4" y="-5.08" length="middle" rot="R180"/>
<pin name="PD3(INT1)" x="25.4" y="-2.54" length="middle" rot="R180"/>
<pin name="PD2(INT0)" x="25.4" y="0" length="middle" rot="R180"/>
<pin name="PD1(TXD)" x="25.4" y="2.54" length="middle" rot="R180"/>
<pin name="PD0(RXD)" x="25.4" y="5.08" length="middle" rot="R180"/>
<pin name="PC5(ADC5/SCL)" x="25.4" y="15.24" length="middle" rot="R180"/>
<pin name="PC4(ADC4/SDA)" x="25.4" y="17.78" length="middle" rot="R180"/>
<pin name="PC3(ADC3)" x="25.4" y="20.32" length="middle" rot="R180"/>
<pin name="PC2(ADC2)" x="25.4" y="22.86" length="middle" rot="R180"/>
<pin name="PC1(ADC1)" x="25.4" y="25.4" length="middle" rot="R180"/>
<pin name="PC0(ADC0)" x="25.4" y="27.94" length="middle" rot="R180"/>
<pin name="PC6(/RESET)" x="-22.86" y="27.94" length="middle" function="dot"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="1206C" prefix="C" uservalue="yes">
<description>4.7uF RS 538-2335   100nF  RS 264-4179</description>
<gates>
<gate name="G$1" symbol="CAP" x="0" y="0"/>
</gates>
<devices>
<device name="" package="1206@1">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="1206R" prefix="R" uservalue="yes">
<gates>
<gate name="G$1" symbol="RES" x="-2.54" y="-2.54"/>
</gates>
<devices>
<device name="" package="1206@1">
<connects>
<connect gate="G$1" pin="P$1" pad="P$1"/>
<connect gate="G$1" pin="P$2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="NO_SW" prefix="SW">
<description>SM NO push button RE 51-0709</description>
<gates>
<gate name="G$1" symbol="SM_NO_PUSH_BUTTON" x="-35.56" y="22.86"/>
</gates>
<devices>
<device name="" package="SM_NO_PUSH_BUTTON">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="MEGA8-P" prefix="IC">
<description>&lt;b&gt;MICROCONTROLLER&lt;/b&gt;&lt;p&gt;
8 Kbytes FLASH, 1 kbytes SRAM, 512 bytes EEPROM, USART, 4-channel 10 bit ADC, 2-channel 8 bit ADC&lt;br&gt;
Pin compatible with Atmega48, ATMega88, ATMega168&lt;br&gt;
Source: avr.lbr</description>
<gates>
<gate name="G$1" symbol="23-I/O-2" x="0" y="0"/>
</gates>
<devices>
<device name="" package="DIL28-3">
<connects>
<connect gate="G$1" pin="AREF" pad="21"/>
<connect gate="G$1" pin="AVCC" pad="20"/>
<connect gate="G$1" pin="GND" pad="22"/>
<connect gate="G$1" pin="GND@1" pad="8"/>
<connect gate="G$1" pin="PB0(ICP)" pad="14"/>
<connect gate="G$1" pin="PB1(OC1A)" pad="15"/>
<connect gate="G$1" pin="PB2(SS/OC1B)" pad="16"/>
<connect gate="G$1" pin="PB3(MOSI/OC2)" pad="17"/>
<connect gate="G$1" pin="PB4(MISO)" pad="18"/>
<connect gate="G$1" pin="PB5(SCK)" pad="19"/>
<connect gate="G$1" pin="PB6(XTAL1/TOSC1)" pad="9"/>
<connect gate="G$1" pin="PB7(XTAL2/TOSC2)" pad="10"/>
<connect gate="G$1" pin="PC0(ADC0)" pad="23"/>
<connect gate="G$1" pin="PC1(ADC1)" pad="24"/>
<connect gate="G$1" pin="PC2(ADC2)" pad="25"/>
<connect gate="G$1" pin="PC3(ADC3)" pad="26"/>
<connect gate="G$1" pin="PC4(ADC4/SDA)" pad="27"/>
<connect gate="G$1" pin="PC5(ADC5/SCL)" pad="28"/>
<connect gate="G$1" pin="PC6(/RESET)" pad="1"/>
<connect gate="G$1" pin="PD0(RXD)" pad="2"/>
<connect gate="G$1" pin="PD1(TXD)" pad="3"/>
<connect gate="G$1" pin="PD2(INT0)" pad="4"/>
<connect gate="G$1" pin="PD3(INT1)" pad="5"/>
<connect gate="G$1" pin="PD4(XCK/T0)" pad="6"/>
<connect gate="G$1" pin="PD5(T1)" pad="11"/>
<connect gate="G$1" pin="PD6(AIN0)" pad="12"/>
<connect gate="G$1" pin="PD7(AIN1)" pad="13"/>
<connect gate="G$1" pin="VCC@1" pad="7"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="supply1">
<description>&lt;b&gt;Supply Symbols&lt;/b&gt;&lt;p&gt;
 GND, VCC, 0V, +5V, -5V, etc.&lt;p&gt;
 Please keep in mind, that these devices are necessary for the
 automatic wiring of the supply signals.&lt;p&gt;
 The pin name defined in the symbol is identical to the net which is to be wired automatically.&lt;p&gt;
 In this library the device names are the same as the pin names of the symbols, therefore the correct signal names appear next to the supply symbols in the schematic.&lt;p&gt;
 &lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="+5V">
<wire x1="1.27" y1="-1.905" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="-1.27" y2="-1.905" width="0.254" layer="94"/>
<text x="-2.54" y="-5.08" size="1.778" layer="96" rot="R90">&gt;VALUE</text>
<pin name="+5V" x="0" y="-2.54" visible="off" length="short" direction="sup" rot="R90"/>
</symbol>
<symbol name="0V">
<wire x1="-1.905" y1="0" x2="1.905" y2="0" width="0.254" layer="94"/>
<text x="-1.905" y="-2.54" size="1.778" layer="96">&gt;VALUE</text>
<pin name="0V" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="+5V" prefix="P+">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="+5V" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="0V" prefix="GND">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="0V" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="1_marko">
<packages>
<package name="4_DIGIT_7SEGMENT_DISPLAY">
<pad name="P$1" x="0" y="0" drill="0.8" shape="square"/>
<pad name="P$2" x="2.54" y="0" drill="0.8" shape="square"/>
<pad name="P$3" x="5.08" y="0" drill="0.8" shape="square"/>
<pad name="P$4" x="7.62" y="0" drill="0.8" shape="square"/>
<pad name="P$5" x="10.16" y="0" drill="0.8" shape="square"/>
<pad name="P$6" x="12.7" y="0" drill="0.8" shape="square"/>
<pad name="P$7" x="12.7" y="15.24" drill="0.8" shape="square"/>
<pad name="P$8" x="10.16" y="15.24" drill="0.8" shape="square"/>
<pad name="P$9" x="7.62" y="15.24" drill="0.8" shape="square"/>
<pad name="P$10" x="5.08" y="15.24" drill="0.8" shape="square"/>
<pad name="P$11" x="2.54" y="15.24" drill="0.8" shape="square"/>
<pad name="P$12" x="0" y="15.24" drill="0.8" shape="square"/>
<wire x1="-19.05" y1="17.145" x2="31.75" y2="17.145" width="0.127" layer="21"/>
<wire x1="31.75" y1="17.145" x2="31.75" y2="-1.905" width="0.127" layer="21"/>
<wire x1="31.75" y1="-1.905" x2="-19.05" y2="-1.905" width="0.127" layer="21"/>
<wire x1="-19.05" y1="-1.905" x2="-19.05" y2="17.145" width="0.127" layer="21"/>
<text x="-10.16" y="15.24" size="1.27" layer="21">&gt;NAME</text>
<text x="15.24" y="0" size="1.27" layer="21">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="4_DIGIT_7SEGMENT_DISPLAY">
<pin name="E" x="-2.54" y="-12.7" visible="pin" length="short"/>
<pin name="D" x="-2.54" y="-10.16" visible="pin" length="short"/>
<pin name="CLON" x="-2.54" y="-7.62" visible="pin" length="short"/>
<pin name="C" x="-2.54" y="-5.08" visible="pin" length="short"/>
<pin name="G" x="-2.54" y="-2.54" visible="pin" length="short"/>
<pin name="DIG4" x="-2.54" y="0" visible="pin" length="short"/>
<pin name="B" x="-2.54" y="2.54" visible="pin" length="short"/>
<pin name="DIG3" x="-2.54" y="5.08" visible="pin" length="short"/>
<pin name="DIG2" x="-2.54" y="7.62" visible="pin" length="short"/>
<pin name="F" x="-2.54" y="10.16" visible="pin" length="short"/>
<pin name="A" x="-2.54" y="12.7" visible="pin" length="short"/>
<pin name="DIG1" x="-2.54" y="15.24" visible="pin" length="short"/>
<wire x1="0" y1="17.78" x2="0" y2="-15.24" width="0.254" layer="94"/>
<wire x1="0" y1="-15.24" x2="7.62" y2="-15.24" width="0.254" layer="94"/>
<wire x1="7.62" y1="-15.24" x2="7.62" y2="17.78" width="0.254" layer="94"/>
<wire x1="7.62" y1="17.78" x2="0" y2="17.78" width="0.254" layer="94"/>
<text x="8.89" y="12.7" size="1.778" layer="94" rot="R270">&gt;NAME</text>
<text x="10.16" y="-12.7" size="1.778" layer="94" rot="R90">&gt;VALUE</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="4_DIGIT_7SEGMENT_DISPLAY" prefix="7_SEG">
<description>Common Anode RE 55-1674</description>
<gates>
<gate name="G$1" symbol="4_DIGIT_7SEGMENT_DISPLAY" x="20.32" y="5.08"/>
</gates>
<devices>
<device name="" package="4_DIGIT_7SEGMENT_DISPLAY">
<connects>
<connect gate="G$1" pin="A" pad="P$11"/>
<connect gate="G$1" pin="B" pad="P$7"/>
<connect gate="G$1" pin="C" pad="P$4"/>
<connect gate="G$1" pin="CLON" pad="P$3"/>
<connect gate="G$1" pin="D" pad="P$2"/>
<connect gate="G$1" pin="DIG1" pad="P$12"/>
<connect gate="G$1" pin="DIG2" pad="P$9"/>
<connect gate="G$1" pin="DIG3" pad="P$8"/>
<connect gate="G$1" pin="DIG4" pad="P$6"/>
<connect gate="G$1" pin="E" pad="P$1"/>
<connect gate="G$1" pin="F" pad="P$10"/>
<connect gate="G$1" pin="G" pad="P$5"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="1_3V3_Bootloader">
<packages>
<package name="RE51-0711">
<smd name="P$1" x="0.77" y="1.48" dx="1.5" dy="3" layer="1"/>
<smd name="P$2" x="8.03" y="1.43" dx="1.5" dy="3" layer="1"/>
</package>
</packages>
<symbols>
<symbol name="PB_NO">
<pin name="1" x="0" y="0" length="point" rot="R180"/>
<pin name="2" x="15.24" y="0" length="point"/>
<circle x="4.445" y="0" radius="0.898025" width="0.254" layer="94"/>
<circle x="10.795" y="0" radius="0.898025" width="0.254" layer="94"/>
<wire x1="4.445" y1="0" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="10.795" y1="0" x2="15.24" y2="0" width="0.254" layer="94"/>
<wire x1="4.445" y1="0" x2="11.43" y2="1.905" width="0.254" layer="94"/>
<text x="3.81" y="-3.175" size="1.778" layer="94">&gt;NAME</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="NO_PB_1" prefix="SW">
<description>RE 51-0711</description>
<gates>
<gate name="G$1" symbol="PB_NO" x="-30.48" y="20.32"/>
</gates>
<devices>
<device name="" package="RE51-0711">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="home_library">
<packages>
<package name="CP2102">
<pad name="P$1" x="0" y="-5.08" drill="1" shape="square"/>
<pad name="P$2" x="0" y="-2.54" drill="1" shape="square"/>
<pad name="P$3" x="0" y="0" drill="1" shape="square"/>
<pad name="P$4" x="0" y="2.54" drill="1" shape="square"/>
<pad name="P$5" x="0" y="5.08" drill="1" shape="square"/>
<pad name="P$6" x="0" y="7.62" drill="1" shape="square"/>
<wire x1="-21.59" y1="-6.35" x2="-21.59" y2="8.89" width="0.127" layer="21"/>
<wire x1="-21.59" y1="8.89" x2="1.27" y2="8.89" width="0.127" layer="21"/>
<wire x1="1.27" y1="8.89" x2="1.27" y2="-6.35" width="0.127" layer="21"/>
<wire x1="1.27" y1="-6.35" x2="-21.59" y2="-6.35" width="0.127" layer="21"/>
<text x="-20.32" y="6.35" size="1.27" layer="21">&gt;NAME</text>
<text x="-19.05" y="-5.08" size="1.27" layer="21">&gt;VALUE</text>
</package>
<package name="SOT23" urn="urn:adsk.eagle:footprint:28669/1" locally_modified="yes">
<description>&lt;b&gt;SOT-23&lt;/b&gt;</description>
<wire x1="1.4224" y1="0.6604" x2="1.4224" y2="-0.6604" width="0.1524" layer="51"/>
<wire x1="1.4224" y1="-0.6604" x2="-1.4224" y2="-0.6604" width="0.1524" layer="51"/>
<wire x1="-1.4224" y1="-0.6604" x2="-1.4224" y2="0.6604" width="0.1524" layer="51"/>
<wire x1="-1.4224" y1="0.6604" x2="1.4224" y2="0.6604" width="0.1524" layer="51"/>
<smd name="3" x="0" y="1.35" dx="1" dy="2" layer="1"/>
<smd name="2" x="0.95" y="-1.35" dx="1" dy="2" layer="1"/>
<smd name="1" x="-0.95" y="-1.35" dx="1" dy="2" layer="1"/>
<text x="-1.905" y="2.905" size="1.27" layer="25">&gt;NAME</text>
<text x="-1.905" y="-4.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-0.2286" y1="0.7112" x2="0.2286" y2="1.2954" layer="51"/>
<rectangle x1="0.7112" y1="-1.2954" x2="1.1684" y2="-0.7112" layer="51"/>
<rectangle x1="-1.1684" y1="-1.2954" x2="-0.7112" y2="-0.7112" locked="yes" layer="51"/>
</package>
<package name="ATTINY1606">
<smd name="P$1" x="-5.08" y="-1.27" dx="0.6" dy="3" layer="1" rot="R180"/>
<smd name="P$2" x="-3.81" y="-1.27" dx="0.6" dy="3" layer="1" rot="R180"/>
<smd name="P$3" x="-2.54" y="-1.27" dx="0.6" dy="3" layer="1" rot="R180"/>
<smd name="P$4" x="-1.27" y="-1.27" dx="0.6" dy="3" layer="1" rot="R180"/>
<smd name="P$5" x="0" y="-1.27" dx="0.6" dy="3" layer="1" rot="R180"/>
<smd name="P$6" x="1.27" y="-1.27" dx="0.6" dy="3" layer="1" rot="R180"/>
<smd name="P$7" x="2.54" y="-1.27" dx="0.6" dy="3" layer="1" rot="R180"/>
<smd name="P$8" x="3.81" y="-1.27" dx="0.6" dy="3" layer="1" rot="R180"/>
<smd name="P$9" x="5.08" y="-1.27" dx="0.6" dy="3" layer="1" rot="R180"/>
<smd name="P$10" x="6.35" y="-1.27" dx="0.6" dy="3" layer="1" rot="R180"/>
<smd name="P$11" x="6.2434" y="8.5702" dx="0.6" dy="3" layer="1"/>
<smd name="P$12" x="4.9734" y="8.5702" dx="0.6" dy="3" layer="1"/>
<smd name="P$13" x="3.7034" y="8.5702" dx="0.6" dy="3" layer="1"/>
<smd name="P$14" x="2.4334" y="8.5702" dx="0.6" dy="3" layer="1"/>
<smd name="P$15" x="1.1634" y="8.5702" dx="0.6" dy="3" layer="1"/>
<smd name="P$16" x="-0.1066" y="8.5702" dx="0.6" dy="3" layer="1"/>
<smd name="P$17" x="-1.3766" y="8.5702" dx="0.6" dy="3" layer="1"/>
<smd name="P$18" x="-2.6466" y="8.5702" dx="0.6" dy="3" layer="1"/>
<smd name="P$19" x="-3.9166" y="8.5702" dx="0.6" dy="3" layer="1"/>
<smd name="P$20" x="-5.1866" y="8.5702" dx="0.6" dy="3" layer="1"/>
<wire x1="6.985" y1="6.35" x2="-5.715" y2="6.35" width="0.127" layer="21"/>
<wire x1="-5.715" y1="6.35" x2="-5.715" y2="0.635" width="0.127" layer="21"/>
<wire x1="-5.715" y1="0.635" x2="6.985" y2="0.635" width="0.127" layer="21"/>
<wire x1="6.985" y1="0.635" x2="6.985" y2="6.35" width="0.127" layer="21"/>
<circle x="-4.826" y="1.27" radius="0.508" width="0.127" layer="21"/>
<text x="-6.35" y="0" size="1.27" layer="21" rot="R90">&gt;NAME</text>
<text x="8.89" y="0" size="1.27" layer="21" rot="R90">&gt;VALUE</text>
</package>
</packages>
<packages3d>
<package3d name="SOT23" urn="urn:adsk.eagle:package:28738/2" type="model">
<description>SOT-23</description>
<packageinstances>
<packageinstance name="SOT23"/>
</packageinstances>
</package3d>
</packages3d>
<symbols>
<symbol name="CP2102_MODULE">
<pin name="+5V" x="0" y="0" length="short" rot="R180"/>
<pin name="GND" x="0" y="2.54" length="short" rot="R180"/>
<pin name="TXO" x="0" y="5.08" length="short" rot="R180"/>
<pin name="RXI" x="0" y="7.62" length="short" rot="R180"/>
<pin name="DTR" x="0" y="10.16" length="short" rot="R180"/>
<pin name="3V3" x="0" y="12.7" length="short" rot="R180"/>
<wire x1="-2.54" y1="15.24" x2="-2.54" y2="-2.54" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-2.54" x2="-17.78" y2="-2.54" width="0.254" layer="94"/>
<wire x1="-17.78" y1="-2.54" x2="-17.78" y2="15.24" width="0.254" layer="94"/>
<wire x1="-17.78" y1="15.24" x2="-2.54" y2="15.24" width="0.254" layer="94"/>
<text x="-17.78" y="16.51" size="1.778" layer="94">&gt;NAME</text>
<text x="-15.24" y="-5.08" size="1.778" layer="94">&gt;VALUE</text>
<text x="-15.24" y="2.54" size="1.778" layer="94" rot="R90">CP2102</text>
<text x="-12.7" y="-1.27" size="1.778" layer="94" rot="R90">USB to UART</text>
</symbol>
<symbol name="N-MOSFET">
<wire x1="0.762" y1="0.762" x2="0.762" y2="0" width="0.254" layer="94"/>
<wire x1="0.762" y1="0" x2="0.762" y2="-0.762" width="0.254" layer="94"/>
<wire x1="0.762" y1="3.175" x2="0.762" y2="2.54" width="0.254" layer="94"/>
<wire x1="0.762" y1="2.54" x2="0.762" y2="1.905" width="0.254" layer="94"/>
<wire x1="0.762" y1="0" x2="2.54" y2="0" width="0.1524" layer="94"/>
<wire x1="2.54" y1="0" x2="2.54" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="0.762" y1="-1.905" x2="0.762" y2="-2.54" width="0.254" layer="94"/>
<wire x1="0.762" y1="-2.54" x2="0.762" y2="-3.175" width="0.254" layer="94"/>
<wire x1="0" y1="2.54" x2="0" y2="-2.54" width="0.254" layer="94"/>
<wire x1="2.54" y1="-2.54" x2="0.762" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="3.81" y1="2.54" x2="3.81" y2="0.508" width="0.1524" layer="94"/>
<wire x1="3.81" y1="0.508" x2="3.81" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="2.54" y1="-2.54" x2="3.81" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="0.762" y1="2.54" x2="3.81" y2="2.54" width="0.1524" layer="94"/>
<wire x1="4.572" y1="0.762" x2="4.318" y2="0.508" width="0.1524" layer="94"/>
<wire x1="4.318" y1="0.508" x2="3.81" y2="0.508" width="0.1524" layer="94"/>
<wire x1="3.81" y1="0.508" x2="3.302" y2="0.508" width="0.1524" layer="94"/>
<wire x1="3.302" y1="0.508" x2="3.048" y2="0.254" width="0.1524" layer="94"/>
<circle x="2.54" y="-2.54" radius="0.3592" width="0" layer="94"/>
<circle x="2.54" y="2.54" radius="0.3592" width="0" layer="94"/>
<text x="-11.43" y="0" size="1.778" layer="96">&gt;VALUE</text>
<text x="-11.43" y="2.54" size="1.778" layer="95">&gt;NAME</text>
<pin name="S" x="2.54" y="-5.08" visible="off" length="short" direction="pas" rot="R90"/>
<pin name="G" x="-2.54" y="-2.54" visible="off" length="short" direction="pas"/>
<pin name="D" x="2.54" y="5.08" visible="off" length="short" direction="pas" rot="R270"/>
<polygon width="0.1524" layer="94">
<vertex x="3.81" y="0.508"/>
<vertex x="3.302" y="-0.254"/>
<vertex x="4.318" y="-0.254"/>
</polygon>
<polygon width="0.1524" layer="94">
<vertex x="1.016" y="0"/>
<vertex x="2.032" y="0.762"/>
<vertex x="2.032" y="-0.762"/>
</polygon>
</symbol>
<symbol name="ATTINY1606">
<pin name="VDD" x="-7.62" y="15.24" length="short"/>
<pin name="PA4" x="-7.62" y="12.7" length="short"/>
<pin name="PA5" x="-7.62" y="10.16" length="short"/>
<pin name="PA6" x="-7.62" y="7.62" length="short"/>
<pin name="PA7" x="-7.62" y="5.08" length="short"/>
<pin name="PB5" x="-7.62" y="2.54" length="short"/>
<pin name="PB4" x="-7.62" y="0" length="short"/>
<pin name="PB3" x="-7.62" y="-2.54" length="short"/>
<pin name="PB2" x="-7.62" y="-5.08" length="short"/>
<pin name="PB1" x="-7.62" y="-7.62" length="short"/>
<pin name="PB0" x="12.7" y="-7.62" length="short" rot="R180"/>
<pin name="PC0" x="12.7" y="-5.08" length="short" rot="R180"/>
<pin name="PC1" x="12.7" y="-2.54" length="short" rot="R180"/>
<pin name="PC2" x="12.7" y="0" length="short" rot="R180"/>
<pin name="PC3" x="12.7" y="2.54" length="short" rot="R180"/>
<pin name="RST" x="12.7" y="5.08" length="short" rot="R180"/>
<pin name="PA1" x="12.7" y="7.62" length="short" rot="R180"/>
<pin name="PA2" x="12.7" y="10.16" length="short" rot="R180"/>
<pin name="PA3" x="12.7" y="12.7" length="short" rot="R180"/>
<pin name="0V" x="12.7" y="15.24" length="short" rot="R180"/>
<text x="-7.62" y="17.78" size="1.778" layer="97">&gt;VALUE</text>
<text x="5.08" y="-12.7" size="1.778" layer="95">&gt;NAME</text>
<wire x1="-5.08" y1="16.51" x2="10.16" y2="16.51" width="0.254" layer="97"/>
<wire x1="10.16" y1="16.51" x2="10.16" y2="-8.89" width="0.254" layer="97"/>
<wire x1="10.16" y1="-8.89" x2="-5.08" y2="-8.89" width="0.254" layer="97"/>
<wire x1="-5.08" y1="-8.89" x2="-5.08" y2="16.51" width="0.254" layer="97"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="CP2102" prefix="MOD">
<gates>
<gate name="G$1" symbol="CP2102_MODULE" x="0" y="0"/>
</gates>
<devices>
<device name="" package="CP2102">
<connects>
<connect gate="G$1" pin="+5V" pad="P$1"/>
<connect gate="G$1" pin="3V3" pad="P$6"/>
<connect gate="G$1" pin="DTR" pad="P$5"/>
<connect gate="G$1" pin="GND" pad="P$2"/>
<connect gate="G$1" pin="RXI" pad="P$4"/>
<connect gate="G$1" pin="TXO" pad="P$3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="BSS138" prefix="Q">
<gates>
<gate name="G$1" symbol="N-MOSFET" x="2.54" y="2.54"/>
</gates>
<devices>
<device name="" package="SOT23">
<connects>
<connect gate="G$1" pin="D" pad="3"/>
<connect gate="G$1" pin="G" pad="1"/>
<connect gate="G$1" pin="S" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:28738/2"/>
</package3dinstances>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="ATTINY1606" prefix="IC">
<gates>
<gate name="G$1" symbol="ATTINY1606" x="-5.08" y="17.78"/>
</gates>
<devices>
<device name="" package="ATTINY1606">
<connects>
<connect gate="G$1" pin="0V" pad="P$20"/>
<connect gate="G$1" pin="PA1" pad="P$17"/>
<connect gate="G$1" pin="PA2" pad="P$18"/>
<connect gate="G$1" pin="PA3" pad="P$19"/>
<connect gate="G$1" pin="PA4" pad="P$2"/>
<connect gate="G$1" pin="PA5" pad="P$3"/>
<connect gate="G$1" pin="PA6" pad="P$4"/>
<connect gate="G$1" pin="PA7" pad="P$5"/>
<connect gate="G$1" pin="PB0" pad="P$11"/>
<connect gate="G$1" pin="PB1" pad="P$10"/>
<connect gate="G$1" pin="PB2" pad="P$9"/>
<connect gate="G$1" pin="PB3" pad="P$8"/>
<connect gate="G$1" pin="PB4" pad="P$7"/>
<connect gate="G$1" pin="PB5" pad="P$6"/>
<connect gate="G$1" pin="PC0" pad="P$12"/>
<connect gate="G$1" pin="PC1" pad="P$13"/>
<connect gate="G$1" pin="PC2" pad="P$14"/>
<connect gate="G$1" pin="PC3" pad="P$15"/>
<connect gate="G$1" pin="RST" pad="P$16"/>
<connect gate="G$1" pin="VDD" pad="P$1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="mo">
<packages>
<package name="XTAL">
<pad name="P$1" x="0" y="-1.27" drill="0.6" shape="square"/>
<pad name="P$2" x="0" y="1.27" drill="0.6" shape="square"/>
</package>
</packages>
<symbols>
<symbol name="EXTAL">
<wire x1="7.62" y1="2.54" x2="-5.08" y2="2.54" width="0.254" layer="94"/>
<wire x1="-5.08" y1="2.54" x2="-5.08" y2="-2.54" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-2.54" x2="7.62" y2="-2.54" width="0.254" layer="94"/>
<pin name="P$1" x="12.7" y="1.27" length="middle" rot="R180"/>
<pin name="P$2" x="12.7" y="-1.27" length="middle" rot="R180"/>
<wire x1="7.62" y1="2.54" x2="7.62" y2="-2.54" width="0.254" layer="94"/>
<text x="-5.08" y="3.81" size="1.778" layer="94">&gt;Extal</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="XTAL">
<gates>
<gate name="G$1" symbol="EXTAL" x="-30.48" y="30.48"/>
</gates>
<devices>
<device name="" package="XTAL">
<connects>
<connect gate="G$1" pin="P$1" pad="P$1"/>
<connect gate="G$1" pin="P$2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="R8" library="1_Home_library" deviceset="1206R" device="" value="10K"/>
<part name="P+3" library="supply1" deviceset="+5V" device=""/>
<part name="7_SEG2" library="1_marko" deviceset="4_DIGIT_7SEGMENT_DISPLAY" device=""/>
<part name="7_SEG1" library="1_marko" deviceset="4_DIGIT_7SEGMENT_DISPLAY" device=""/>
<part name="R24" library="1_Home_library" deviceset="1206R" device="" value="220"/>
<part name="R20" library="1_Home_library" deviceset="1206R" device="" value="220"/>
<part name="R25" library="1_Home_library" deviceset="1206R" device="" value="220"/>
<part name="R26" library="1_Home_library" deviceset="1206R" device="" value="220"/>
<part name="R21" library="1_Home_library" deviceset="1206R" device="" value="220"/>
<part name="R22" library="1_Home_library" deviceset="1206R" device="" value="220"/>
<part name="R23" library="1_Home_library" deviceset="1206R" device="" value="220"/>
<part name="P+1" library="supply1" deviceset="+5V" device=""/>
<part name="R2" library="1_Home_library" deviceset="1206R" device="" value="10K"/>
<part name="R3" library="1_Home_library" deviceset="1206R" device="" value="10K"/>
<part name="IC2" library="1_Home_library" deviceset="MEGA8-P" device=""/>
<part name="P+5" library="supply1" deviceset="+5V" device=""/>
<part name="P+6" library="supply1" deviceset="+5V" device=""/>
<part name="GND6" library="supply1" deviceset="0V" device=""/>
<part name="GND5" library="supply1" deviceset="0V" device=""/>
<part name="SW4" library="1_3V3_Bootloader" deviceset="NO_PB_1" device=""/>
<part name="R27" library="1_Home_library" deviceset="1206R" device="" value="220"/>
<part name="R19" library="1_Home_library" deviceset="1206R" device="" value="220"/>
<part name="C16" library="1_Home_library" deviceset="1206C" device="" value="10nF"/>
<part name="C15" library="1_Home_library" deviceset="1206C" device="" value="10nF"/>
<part name="SW3" library="1_3V3_Bootloader" deviceset="NO_PB_1" device=""/>
<part name="GND14" library="supply1" deviceset="0V" device=""/>
<part name="LED1" library="3_My_prog" deviceset="LED" device=""/>
<part name="GND12" library="supply1" deviceset="0V" device=""/>
<part name="R15" library="1_Home_library" deviceset="1206R" device="" value="560"/>
<part name="R16" library="1_Home_library" deviceset="1206R" device="" value="560"/>
<part name="SW5" library="1_3V3_Bootloader" deviceset="NO_PB_1" device=""/>
<part name="R28" library="1_Home_library" deviceset="1206R" device="" value="220"/>
<part name="C17" library="1_Home_library" deviceset="1206C" device="" value="10nF"/>
<part name="GND1" library="supply1" deviceset="0V" device=""/>
<part name="R1" library="1_Home_library" deviceset="1206R" device="" value="220"/>
<part name="SW1" library="1_Home_library" deviceset="NO_SW" device=""/>
<part name="Q1" library="home_library" deviceset="BSS138" device="" package3d_urn="urn:adsk.eagle:package:28738/2"/>
<part name="MOD1" library="home_library" deviceset="CP2102" device=""/>
<part name="IC1" library="home_library" deviceset="ATTINY1606" device=""/>
<part name="GND2" library="supply1" deviceset="0V" device=""/>
<part name="P+2" library="supply1" deviceset="+5V" device=""/>
<part name="C1" library="1_Home_library" deviceset="1206C" device="" value="4.7uF"/>
<part name="C2" library="1_Home_library" deviceset="1206C" device="" value="100nF"/>
<part name="C4" library="1_Home_library" deviceset="1206C" device="" value="100nF"/>
<part name="C5" library="1_Home_library" deviceset="1206C" device="" value="4.7uF"/>
<part name="C6" library="1_Home_library" deviceset="1206C" device="" value="100nF"/>
<part name="C3" library="1_Home_library" deviceset="1206C" device="" value="4.7uF"/>
<part name="U$1" library="mo" deviceset="XTAL" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="R8" gate="G$1" x="-72.39" y="154.94" smashed="yes" rot="R90">
<attribute name="VALUE" x="-72.898" y="158.242" size="1.778" layer="94" rot="R90"/>
<attribute name="NAME" x="-70.104" y="158.242" size="1.778" layer="94" rot="R90"/>
</instance>
<instance part="P+3" gate="1" x="-72.39" y="173.99" smashed="yes">
<attribute name="VALUE" x="-74.93" y="168.91" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="7_SEG2" gate="G$1" x="187.96" y="151.13" smashed="yes">
<attribute name="NAME" x="196.85" y="163.83" size="1.778" layer="94" rot="R270"/>
<attribute name="VALUE" x="200.66" y="115.57" size="1.778" layer="94" rot="R90"/>
</instance>
<instance part="7_SEG1" gate="G$1" x="187.96" y="198.12" smashed="yes">
<attribute name="NAME" x="196.85" y="210.82" size="1.778" layer="94" rot="R270"/>
<attribute name="VALUE" x="203.2" y="182.88" size="1.778" layer="94" rot="R90"/>
</instance>
<instance part="R24" gate="G$1" x="132.08" y="182.88" smashed="yes" rot="R180">
<attribute name="VALUE" x="138.938" y="184.912" size="1.778" layer="94" rot="R180"/>
<attribute name="NAME" x="128.778" y="185.166" size="1.778" layer="94" rot="R180"/>
</instance>
<instance part="R20" gate="G$1" x="134.62" y="180.34" smashed="yes" rot="MR180">
<attribute name="VALUE" x="126.492" y="182.372" size="1.778" layer="94" rot="MR180"/>
<attribute name="NAME" x="136.652" y="182.626" size="1.778" layer="94" rot="MR180"/>
</instance>
<instance part="R25" gate="G$1" x="137.16" y="177.8" smashed="yes" rot="R180">
<attribute name="VALUE" x="144.018" y="179.832" size="1.778" layer="94" rot="R180"/>
<attribute name="NAME" x="133.858" y="180.086" size="1.778" layer="94" rot="R180"/>
</instance>
<instance part="R26" gate="G$1" x="139.7" y="175.26" smashed="yes" rot="R180">
<attribute name="VALUE" x="146.558" y="177.292" size="1.778" layer="94" rot="R180"/>
<attribute name="NAME" x="136.398" y="177.546" size="1.778" layer="94" rot="R180"/>
</instance>
<instance part="R21" gate="G$1" x="140.97" y="172.72" smashed="yes" rot="R180">
<attribute name="VALUE" x="149.098" y="174.752" size="1.778" layer="94" rot="R180"/>
<attribute name="NAME" x="137.668" y="175.006" size="1.778" layer="94" rot="R180"/>
</instance>
<instance part="R22" gate="G$1" x="144.78" y="170.18" smashed="yes" rot="R180">
<attribute name="VALUE" x="151.638" y="172.212" size="1.778" layer="94" rot="R180"/>
<attribute name="NAME" x="141.478" y="172.466" size="1.778" layer="94" rot="R180"/>
</instance>
<instance part="R23" gate="G$1" x="146.05" y="167.64" smashed="yes" rot="R180">
<attribute name="VALUE" x="152.908" y="169.672" size="1.778" layer="94" rot="R180"/>
<attribute name="NAME" x="142.748" y="169.926" size="1.778" layer="94" rot="R180"/>
</instance>
<instance part="P+1" gate="1" x="-100.33" y="166.37" smashed="yes">
<attribute name="VALUE" x="-102.87" y="161.29" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="R2" gate="G$1" x="-124.46" y="143.51" smashed="yes" rot="R90">
<attribute name="VALUE" x="-124.968" y="146.812" size="1.778" layer="94" rot="R90"/>
<attribute name="NAME" x="-122.174" y="146.812" size="1.778" layer="94" rot="R90"/>
</instance>
<instance part="R3" gate="G$1" x="-107.95" y="152.4" smashed="yes" rot="R90">
<attribute name="VALUE" x="-108.458" y="155.702" size="1.778" layer="94" rot="R90"/>
<attribute name="NAME" x="-105.664" y="155.702" size="1.778" layer="94" rot="R90"/>
</instance>
<instance part="IC2" gate="G$1" x="-6.35" y="40.64" smashed="yes">
<attribute name="NAME" x="-24.13" y="5.08" size="1.778" layer="95"/>
<attribute name="VALUE" x="-24.13" y="72.39" size="1.778" layer="96"/>
</instance>
<instance part="P+5" gate="1" x="-53.34" y="80.01" smashed="yes">
<attribute name="VALUE" x="-55.88" y="74.93" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="P+6" gate="1" x="-29.21" y="25.4" smashed="yes" rot="R180">
<attribute name="VALUE" x="-26.67" y="30.48" size="1.778" layer="96" rot="R270"/>
</instance>
<instance part="GND6" gate="1" x="-33.02" y="25.4" smashed="yes">
<attribute name="VALUE" x="-34.925" y="22.86" size="1.778" layer="96"/>
</instance>
<instance part="GND5" gate="1" x="-68.58" y="63.5" smashed="yes" rot="R270">
<attribute name="VALUE" x="-71.12" y="65.405" size="1.778" layer="96" rot="R270"/>
</instance>
<instance part="SW4" gate="G$1" x="143.51" y="11.43" smashed="yes" rot="MR90">
<attribute name="NAME" x="140.335" y="15.24" size="1.778" layer="94" rot="MR90"/>
</instance>
<instance part="R27" gate="G$1" x="138.43" y="31.75" smashed="yes" rot="MR180">
<attribute name="VALUE" x="131.572" y="33.782" size="1.778" layer="94" rot="MR180"/>
<attribute name="NAME" x="141.732" y="34.036" size="1.778" layer="94" rot="MR180"/>
</instance>
<instance part="R19" gate="G$1" x="114.3" y="30.48" smashed="yes" rot="MR180">
<attribute name="VALUE" x="107.442" y="32.512" size="1.778" layer="94" rot="MR180"/>
<attribute name="NAME" x="117.602" y="32.766" size="1.778" layer="94" rot="MR180"/>
</instance>
<instance part="C16" gate="G$1" x="130.81" y="13.97" smashed="yes" rot="MR90">
<attribute name="VALUE" x="127" y="12.7" size="1.27" layer="96" rot="MR90"/>
<attribute name="NAME" x="133.35" y="11.43" size="1.778" layer="95" rot="MR90"/>
</instance>
<instance part="C15" gate="G$1" x="107.95" y="17.78" smashed="yes" rot="MR90">
<attribute name="VALUE" x="104.14" y="16.51" size="1.27" layer="96" rot="MR90"/>
<attribute name="NAME" x="110.49" y="15.24" size="1.778" layer="95" rot="MR90"/>
</instance>
<instance part="SW3" gate="G$1" x="119.38" y="12.7" smashed="yes" rot="MR90">
<attribute name="NAME" x="116.205" y="16.51" size="1.778" layer="94" rot="MR90"/>
</instance>
<instance part="GND14" gate="1" x="134.62" y="0" smashed="yes">
<attribute name="VALUE" x="132.715" y="-2.54" size="1.778" layer="96"/>
</instance>
<instance part="LED1" gate="G$1" x="71.12" y="45.72" smashed="yes" rot="MR180">
<attribute name="NAME" x="71.882" y="43.434" size="1.778" layer="94" rot="MR180"/>
</instance>
<instance part="GND12" gate="1" x="77.47" y="45.72" smashed="yes" rot="MR270">
<attribute name="VALUE" x="80.01" y="47.625" size="1.778" layer="96" rot="MR270"/>
</instance>
<instance part="R15" gate="G$1" x="64.77" y="41.91" smashed="yes" rot="R180">
<attribute name="VALUE" x="61.468" y="41.402" size="1.778" layer="94" rot="R180"/>
<attribute name="NAME" x="61.468" y="44.196" size="1.778" layer="94" rot="R180"/>
</instance>
<instance part="R16" gate="G$1" x="63.5" y="49.53" smashed="yes">
<attribute name="VALUE" x="66.802" y="50.038" size="1.778" layer="94"/>
<attribute name="NAME" x="66.802" y="47.244" size="1.778" layer="94"/>
</instance>
<instance part="SW5" gate="G$1" x="176.53" y="11.43" smashed="yes" rot="MR90">
<attribute name="NAME" x="173.355" y="15.24" size="1.778" layer="94" rot="MR90"/>
</instance>
<instance part="R28" gate="G$1" x="171.45" y="31.75" smashed="yes" rot="MR180">
<attribute name="VALUE" x="164.592" y="33.782" size="1.778" layer="94" rot="MR180"/>
<attribute name="NAME" x="174.752" y="34.036" size="1.778" layer="94" rot="MR180"/>
</instance>
<instance part="C17" gate="G$1" x="154.94" y="13.97" smashed="yes" rot="MR90">
<attribute name="VALUE" x="151.13" y="12.7" size="1.27" layer="96" rot="MR90"/>
<attribute name="NAME" x="157.48" y="11.43" size="1.778" layer="95" rot="MR90"/>
</instance>
<instance part="GND1" gate="1" x="-86.36" y="68.58" smashed="yes">
<attribute name="VALUE" x="-88.265" y="66.04" size="1.778" layer="96"/>
</instance>
<instance part="R1" gate="G$1" x="148.59" y="165.1" smashed="yes" rot="R180">
<attribute name="VALUE" x="155.448" y="167.132" size="1.778" layer="94" rot="R180"/>
<attribute name="NAME" x="145.288" y="167.386" size="1.778" layer="94" rot="R180"/>
</instance>
<instance part="SW1" gate="G$1" x="92.71" y="13.97" smashed="yes" rot="R90"/>
<instance part="Q1" gate="G$1" x="-115.57" y="139.7" smashed="yes" rot="R270">
<attribute name="VALUE" x="-115.57" y="151.13" size="1.778" layer="96" rot="R270"/>
<attribute name="NAME" x="-113.03" y="151.13" size="1.778" layer="95" rot="R270"/>
</instance>
<instance part="MOD1" gate="G$1" x="-91.44" y="91.44" smashed="yes">
<attribute name="NAME" x="-109.22" y="107.95" size="1.778" layer="94"/>
<attribute name="VALUE" x="-106.68" y="86.36" size="1.778" layer="94"/>
</instance>
<instance part="IC1" gate="G$1" x="48.26" y="147.32" smashed="yes">
<attribute name="VALUE" x="40.64" y="165.1" size="1.778" layer="97"/>
<attribute name="NAME" x="53.34" y="134.62" size="1.778" layer="95"/>
</instance>
<instance part="GND2" gate="1" x="63.5" y="181.61" smashed="yes" rot="MR180">
<attribute name="VALUE" x="61.595" y="184.15" size="1.778" layer="96" rot="MR180"/>
</instance>
<instance part="P+2" gate="1" x="30.48" y="190.5" smashed="yes">
<attribute name="VALUE" x="27.94" y="185.42" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="C1" gate="G$1" x="-48.26" y="57.15" smashed="yes" rot="MR90">
<attribute name="VALUE" x="-52.07" y="55.88" size="1.27" layer="96" rot="MR90"/>
<attribute name="NAME" x="-45.72" y="54.61" size="1.778" layer="95" rot="MR90"/>
</instance>
<instance part="C2" gate="G$1" x="-39.37" y="57.15" smashed="yes" rot="MR90">
<attribute name="VALUE" x="-43.18" y="55.88" size="1.27" layer="96" rot="MR90"/>
<attribute name="NAME" x="-36.83" y="54.61" size="1.778" layer="95" rot="MR90"/>
</instance>
<instance part="C4" gate="G$1" x="45.72" y="175.26" smashed="yes" rot="MR90">
<attribute name="VALUE" x="41.91" y="173.99" size="1.27" layer="96" rot="MR90"/>
<attribute name="NAME" x="48.26" y="172.72" size="1.778" layer="95" rot="MR90"/>
</instance>
<instance part="C5" gate="G$1" x="-72.39" y="81.28" smashed="yes" rot="MR90">
<attribute name="VALUE" x="-76.2" y="80.01" size="1.27" layer="96" rot="MR90"/>
<attribute name="NAME" x="-69.85" y="78.74" size="1.778" layer="95" rot="MR90"/>
</instance>
<instance part="C6" gate="G$1" x="-63.5" y="81.28" smashed="yes" rot="MR90">
<attribute name="VALUE" x="-67.31" y="80.01" size="1.27" layer="96" rot="MR90"/>
<attribute name="NAME" x="-60.96" y="78.74" size="1.778" layer="95" rot="MR90"/>
</instance>
<instance part="C3" gate="G$1" x="-81.28" y="81.28" smashed="yes" rot="MR90">
<attribute name="VALUE" x="-85.09" y="80.01" size="1.27" layer="96" rot="MR90"/>
<attribute name="NAME" x="-78.74" y="78.74" size="1.778" layer="95" rot="MR90"/>
</instance>
<instance part="U$1" gate="G$1" x="-63.5" y="43.18" smashed="yes"/>
</instances>
<busses>
<bus name="SEVEN_SEG[0..7]">
<segment>
<wire x1="157.48" y1="214.63" x2="158.75" y2="214.63" width="0.762" layer="92"/>
<wire x1="158.75" y1="214.63" x2="158.75" y2="137.16" width="0.762" layer="92"/>
</segment>
</bus>
<bus name="DIGIT0,DIGIT1,DIGIT2,DIGIT3,DIGIT4,DIGIT5,DIGIT6,DIGIT7,DISPLAY_DRIVER[0..7]">
<segment>
<wire x1="123.19" y1="182.88" x2="123.19" y2="45.72" width="0.762" layer="92"/>
<wire x1="123.19" y1="45.72" x2="140.97" y2="45.72" width="0.762" layer="92"/>
<wire x1="140.97" y1="45.72" x2="140.97" y2="135.89" width="0.762" layer="92"/>
<wire x1="123.19" y1="182.88" x2="123.19" y2="223.52" width="0.762" layer="92"/>
<wire x1="123.19" y1="223.52" x2="123.19" y2="255.27" width="0.762" layer="92"/>
<wire x1="123.19" y1="255.27" x2="123.19" y2="256.54" width="0.762" layer="92"/>
</segment>
</bus>
<bus name="DIGIT[0..7],DIGIT3,DIGIT5">
<segment>
<wire x1="171.45" y1="219.71" x2="171.45" y2="49.53" width="0.762" layer="92"/>
</segment>
</bus>
</busses>
<nets>
<net name="0V" class="0">
<segment>
<pinref part="GND5" gate="1" pin="0V"/>
<pinref part="IC2" gate="G$1" pin="GND"/>
<wire x1="-66.04" y1="63.5" x2="-48.26" y2="63.5" width="0.1524" layer="91"/>
<pinref part="C1" gate="G$1" pin="2"/>
<wire x1="-48.26" y1="63.5" x2="-39.37" y2="63.5" width="0.1524" layer="91"/>
<wire x1="-39.37" y1="63.5" x2="-29.21" y2="63.5" width="0.1524" layer="91"/>
<wire x1="-48.26" y1="62.23" x2="-48.26" y2="63.5" width="0.1524" layer="91"/>
<junction x="-48.26" y="63.5"/>
<pinref part="C2" gate="G$1" pin="2"/>
<wire x1="-39.37" y1="62.23" x2="-39.37" y2="63.5" width="0.1524" layer="91"/>
<junction x="-39.37" y="63.5"/>
</segment>
<segment>
<pinref part="GND6" gate="1" pin="0V"/>
<wire x1="-33.02" y1="27.94" x2="-33.02" y2="38.1" width="0.1524" layer="91"/>
<pinref part="IC2" gate="G$1" pin="GND@1"/>
<wire x1="-33.02" y1="38.1" x2="-29.21" y2="38.1" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="C16" gate="G$1" pin="1"/>
<wire x1="130.81" y1="8.89" x2="119.38" y2="8.89" width="0.1524" layer="91"/>
<pinref part="C15" gate="G$1" pin="1"/>
<wire x1="119.38" y1="8.89" x2="107.95" y2="8.89" width="0.1524" layer="91"/>
<wire x1="107.95" y1="8.89" x2="107.95" y2="12.7" width="0.1524" layer="91"/>
<pinref part="SW4" gate="G$1" pin="1"/>
<wire x1="143.51" y1="11.43" x2="143.51" y2="8.89" width="0.1524" layer="91"/>
<wire x1="143.51" y1="8.89" x2="134.62" y2="8.89" width="0.1524" layer="91"/>
<junction x="130.81" y="8.89"/>
<pinref part="SW3" gate="G$1" pin="1"/>
<wire x1="134.62" y1="8.89" x2="130.81" y2="8.89" width="0.1524" layer="91"/>
<wire x1="119.38" y1="12.7" x2="119.38" y2="8.89" width="0.1524" layer="91"/>
<junction x="119.38" y="8.89"/>
<wire x1="134.62" y1="8.89" x2="134.62" y2="2.54" width="0.1524" layer="91"/>
<junction x="134.62" y="8.89"/>
<pinref part="GND14" gate="1" pin="0V"/>
<pinref part="C17" gate="G$1" pin="1"/>
<pinref part="SW5" gate="G$1" pin="1"/>
<wire x1="176.53" y1="11.43" x2="176.53" y2="8.89" width="0.1524" layer="91"/>
<wire x1="176.53" y1="8.89" x2="154.94" y2="8.89" width="0.1524" layer="91"/>
<wire x1="143.51" y1="8.89" x2="154.94" y2="8.89" width="0.1524" layer="91"/>
<junction x="143.51" y="8.89"/>
<junction x="154.94" y="8.89"/>
<wire x1="107.95" y1="8.89" x2="99.06" y2="8.89" width="0.1524" layer="91"/>
<junction x="107.95" y="8.89"/>
<wire x1="99.06" y1="8.89" x2="92.71" y2="8.89" width="0.1524" layer="91"/>
<pinref part="SW1" gate="G$1" pin="1"/>
<wire x1="92.71" y1="8.89" x2="92.71" y2="11.43" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="LED1" gate="G$1" pin="2"/>
<pinref part="GND12" gate="1" pin="0V"/>
<wire x1="74.93" y1="45.72" x2="73.66" y2="45.72" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND1" gate="1" pin="0V"/>
<wire x1="-86.36" y1="93.98" x2="-86.36" y2="73.66" width="0.1524" layer="91"/>
<pinref part="MOD1" gate="G$1" pin="GND"/>
<wire x1="-86.36" y1="73.66" x2="-86.36" y2="71.12" width="0.1524" layer="91"/>
<wire x1="-87.63" y1="93.98" x2="-91.44" y2="93.98" width="0.1524" layer="91"/>
<wire x1="-87.63" y1="93.98" x2="-86.36" y2="93.98" width="0.1524" layer="91"/>
<wire x1="-63.5" y1="73.66" x2="-72.39" y2="73.66" width="0.1524" layer="91"/>
<junction x="-86.36" y="73.66"/>
<pinref part="C5" gate="G$1" pin="1"/>
<wire x1="-72.39" y1="73.66" x2="-81.28" y2="73.66" width="0.1524" layer="91"/>
<wire x1="-81.28" y1="73.66" x2="-86.36" y2="73.66" width="0.1524" layer="91"/>
<wire x1="-72.39" y1="76.2" x2="-72.39" y2="73.66" width="0.1524" layer="91"/>
<junction x="-72.39" y="73.66"/>
<pinref part="C6" gate="G$1" pin="1"/>
<wire x1="-63.5" y1="76.2" x2="-63.5" y2="73.66" width="0.1524" layer="91"/>
<pinref part="C3" gate="G$1" pin="1"/>
<wire x1="-81.28" y1="76.2" x2="-81.28" y2="73.66" width="0.1524" layer="91"/>
<junction x="-81.28" y="73.66"/>
</segment>
<segment>
<pinref part="IC1" gate="G$1" pin="0V"/>
<wire x1="60.96" y1="162.56" x2="63.5" y2="162.56" width="0.1524" layer="91"/>
<pinref part="GND2" gate="1" pin="0V"/>
<wire x1="63.5" y1="162.56" x2="63.5" y2="170.18" width="0.1524" layer="91"/>
<pinref part="C4" gate="G$1" pin="1"/>
<wire x1="63.5" y1="170.18" x2="63.5" y2="179.07" width="0.1524" layer="91"/>
<wire x1="45.72" y1="170.18" x2="63.5" y2="170.18" width="0.1524" layer="91"/>
<junction x="63.5" y="170.18"/>
</segment>
</net>
<net name="+5V" class="0">
<segment>
<pinref part="P+3" gate="1" pin="+5V"/>
<pinref part="R8" gate="G$1" pin="P$2"/>
<wire x1="-72.39" y1="171.45" x2="-72.39" y2="160.02" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="P+1" gate="1" pin="+5V"/>
<wire x1="-100.33" y1="163.83" x2="-100.33" y2="161.29" width="0.1524" layer="91"/>
<wire x1="-100.33" y1="161.29" x2="-100.33" y2="140.97" width="0.1524" layer="91"/>
<wire x1="-77.47" y1="140.97" x2="-100.33" y2="140.97" width="0.1524" layer="91"/>
<pinref part="R3" gate="G$1" pin="P$2"/>
<wire x1="-107.95" y1="157.48" x2="-107.95" y2="161.29" width="0.1524" layer="91"/>
<wire x1="-107.95" y1="161.29" x2="-100.33" y2="161.29" width="0.1524" layer="91"/>
<junction x="-100.33" y="161.29"/>
<wire x1="-55.88" y1="91.44" x2="-55.88" y2="135.89" width="0.1524" layer="91"/>
<wire x1="-55.88" y1="135.89" x2="-77.47" y2="135.89" width="0.1524" layer="91"/>
<wire x1="-77.47" y1="135.89" x2="-77.47" y2="140.97" width="0.1524" layer="91"/>
<pinref part="MOD1" gate="G$1" pin="+5V"/>
<wire x1="-91.44" y1="91.44" x2="-81.28" y2="91.44" width="0.1524" layer="91"/>
<pinref part="C6" gate="G$1" pin="2"/>
<wire x1="-81.28" y1="91.44" x2="-72.39" y2="91.44" width="0.1524" layer="91"/>
<wire x1="-72.39" y1="91.44" x2="-63.5" y2="91.44" width="0.1524" layer="91"/>
<wire x1="-63.5" y1="91.44" x2="-55.88" y2="91.44" width="0.1524" layer="91"/>
<wire x1="-63.5" y1="86.36" x2="-63.5" y2="91.44" width="0.1524" layer="91"/>
<junction x="-63.5" y="91.44"/>
<pinref part="C5" gate="G$1" pin="2"/>
<wire x1="-72.39" y1="86.36" x2="-72.39" y2="91.44" width="0.1524" layer="91"/>
<junction x="-72.39" y="91.44"/>
<pinref part="C3" gate="G$1" pin="2"/>
<wire x1="-81.28" y1="86.36" x2="-81.28" y2="91.44" width="0.1524" layer="91"/>
<junction x="-81.28" y="91.44"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="VCC@1"/>
<pinref part="P+6" gate="1" pin="+5V"/>
<wire x1="-29.21" y1="33.02" x2="-29.21" y2="27.94" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="P+5" gate="1" pin="+5V"/>
<wire x1="-53.34" y1="58.42" x2="-53.34" y2="77.47" width="0.1524" layer="91"/>
<wire x1="-53.34" y1="50.8" x2="-53.34" y2="53.34" width="0.1524" layer="91"/>
<wire x1="-53.34" y1="53.34" x2="-53.34" y2="58.42" width="0.1524" layer="91"/>
<pinref part="IC2" gate="G$1" pin="AVCC"/>
<wire x1="-29.21" y1="58.42" x2="-33.02" y2="58.42" width="0.1524" layer="91"/>
<wire x1="-33.02" y1="58.42" x2="-33.02" y2="50.8" width="0.1524" layer="91"/>
<wire x1="-53.34" y1="50.8" x2="-48.26" y2="50.8" width="0.1524" layer="91"/>
<pinref part="C1" gate="G$1" pin="1"/>
<wire x1="-48.26" y1="50.8" x2="-39.37" y2="50.8" width="0.1524" layer="91"/>
<wire x1="-39.37" y1="50.8" x2="-33.02" y2="50.8" width="0.1524" layer="91"/>
<wire x1="-48.26" y1="52.07" x2="-48.26" y2="50.8" width="0.1524" layer="91"/>
<junction x="-48.26" y="50.8"/>
<pinref part="C2" gate="G$1" pin="1"/>
<wire x1="-39.37" y1="52.07" x2="-39.37" y2="50.8" width="0.1524" layer="91"/>
<junction x="-39.37" y="50.8"/>
</segment>
<segment>
<pinref part="IC1" gate="G$1" pin="VDD"/>
<wire x1="40.64" y1="162.56" x2="30.48" y2="162.56" width="0.1524" layer="91"/>
<pinref part="P+2" gate="1" pin="+5V"/>
<wire x1="30.48" y1="162.56" x2="30.48" y2="180.34" width="0.1524" layer="91"/>
<pinref part="C4" gate="G$1" pin="2"/>
<wire x1="30.48" y1="180.34" x2="30.48" y2="187.96" width="0.1524" layer="91"/>
<wire x1="45.72" y1="180.34" x2="30.48" y2="180.34" width="0.1524" layer="91"/>
<junction x="30.48" y="180.34"/>
</segment>
</net>
<net name="N$14" class="0">
<segment>
<pinref part="IC2" gate="G$1" pin="PD1(TXD)"/>
<wire x1="19.05" y1="43.18" x2="35.56" y2="43.18" width="0.1524" layer="91"/>
<wire x1="35.56" y1="43.18" x2="35.56" y2="86.36" width="0.1524" layer="91"/>
<wire x1="35.56" y1="86.36" x2="11.43" y2="86.36" width="0.1524" layer="91"/>
<wire x1="11.43" y1="86.36" x2="11.43" y2="115.57" width="0.1524" layer="91"/>
<wire x1="11.43" y1="115.57" x2="-16.51" y2="115.57" width="0.1524" layer="91"/>
<wire x1="-16.51" y1="115.57" x2="-16.51" y2="125.73" width="0.1524" layer="91"/>
<wire x1="-62.23" y1="99.06" x2="-62.23" y2="125.73" width="0.1524" layer="91"/>
<wire x1="-62.23" y1="125.73" x2="-16.51" y2="125.73" width="0.1524" layer="91"/>
<pinref part="MOD1" gate="G$1" pin="RXI"/>
<wire x1="-91.44" y1="99.06" x2="-62.23" y2="99.06" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$13" class="0">
<segment>
<pinref part="R8" gate="G$1" pin="P$1"/>
<pinref part="IC2" gate="G$1" pin="PC6(/RESET)"/>
<wire x1="-29.21" y1="68.58" x2="-33.02" y2="68.58" width="0.1524" layer="91"/>
<wire x1="-33.02" y1="144.78" x2="-33.02" y2="68.58" width="0.1524" layer="91"/>
<wire x1="-72.39" y1="149.86" x2="-72.39" y2="144.78" width="0.1524" layer="91"/>
<wire x1="-72.39" y1="144.78" x2="-33.02" y2="144.78" width="0.1524" layer="91"/>
</segment>
</net>
<net name="SEVEN_SEG0" class="0">
<segment>
<pinref part="7_SEG1" gate="G$1" pin="A"/>
<wire x1="185.42" y1="210.82" x2="158.75" y2="210.82" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="7_SEG2" gate="G$1" pin="A"/>
<wire x1="185.42" y1="163.83" x2="158.75" y2="163.83" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="R24" gate="G$1" pin="P$1"/>
<wire x1="158.75" y1="182.88" x2="137.16" y2="182.88" width="0.1524" layer="91"/>
</segment>
</net>
<net name="SEVEN_SEG1" class="0">
<segment>
<pinref part="7_SEG1" gate="G$1" pin="B"/>
<wire x1="185.42" y1="200.66" x2="158.75" y2="200.66" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="7_SEG2" gate="G$1" pin="B"/>
<wire x1="185.42" y1="153.67" x2="158.75" y2="153.67" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="158.75" y1="180.34" x2="139.7" y2="180.34" width="0.1524" layer="91"/>
<pinref part="R20" gate="G$1" pin="P$2"/>
</segment>
</net>
<net name="SEVEN_SEG2" class="0">
<segment>
<pinref part="7_SEG1" gate="G$1" pin="C"/>
<wire x1="185.42" y1="193.04" x2="158.75" y2="193.04" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="7_SEG2" gate="G$1" pin="C"/>
<wire x1="185.42" y1="146.05" x2="158.75" y2="146.05" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="R25" gate="G$1" pin="P$1"/>
<wire x1="158.75" y1="177.8" x2="142.24" y2="177.8" width="0.1524" layer="91"/>
</segment>
</net>
<net name="SEVEN_SEG3" class="0">
<segment>
<pinref part="7_SEG1" gate="G$1" pin="D"/>
<wire x1="185.42" y1="187.96" x2="158.75" y2="187.96" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="7_SEG2" gate="G$1" pin="D"/>
<wire x1="185.42" y1="140.97" x2="158.75" y2="140.97" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="R26" gate="G$1" pin="P$1"/>
<wire x1="158.75" y1="175.26" x2="144.78" y2="175.26" width="0.1524" layer="91"/>
</segment>
</net>
<net name="SEVEN_SEG4" class="0">
<segment>
<pinref part="7_SEG1" gate="G$1" pin="E"/>
<wire x1="185.42" y1="185.42" x2="158.75" y2="185.42" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="7_SEG2" gate="G$1" pin="E"/>
<wire x1="185.42" y1="138.43" x2="158.75" y2="138.43" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="R21" gate="G$1" pin="P$1"/>
<wire x1="158.75" y1="172.72" x2="146.05" y2="172.72" width="0.1524" layer="91"/>
</segment>
</net>
<net name="SEVEN_SEG5" class="0">
<segment>
<pinref part="7_SEG1" gate="G$1" pin="F"/>
<wire x1="185.42" y1="208.28" x2="158.75" y2="208.28" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="7_SEG2" gate="G$1" pin="F"/>
<wire x1="185.42" y1="161.29" x2="158.75" y2="161.29" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="R22" gate="G$1" pin="P$1"/>
<wire x1="158.75" y1="170.18" x2="149.86" y2="170.18" width="0.1524" layer="91"/>
</segment>
</net>
<net name="SEVEN_SEG6" class="0">
<segment>
<pinref part="7_SEG1" gate="G$1" pin="G"/>
<wire x1="185.42" y1="195.58" x2="158.75" y2="195.58" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="7_SEG2" gate="G$1" pin="G"/>
<wire x1="185.42" y1="148.59" x2="158.75" y2="148.59" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="R23" gate="G$1" pin="P$1"/>
<wire x1="158.75" y1="167.64" x2="151.13" y2="167.64" width="0.1524" layer="91"/>
</segment>
</net>
<net name="DISPLAY_DRIVER0" class="0">
<segment>
<pinref part="R24" gate="G$1" pin="P$2"/>
<wire x1="127" y1="182.88" x2="123.19" y2="182.88" width="0.1524" layer="91"/>
<label x="100.33" y="182.88" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="123.19" y1="191.77" x2="109.22" y2="191.77" width="0.1524" layer="91"/>
<label x="96.52" y="193.04" size="1.778" layer="95"/>
<wire x1="95.25" y1="135.89" x2="95.25" y2="191.77" width="0.1524" layer="91"/>
<wire x1="34.29" y1="139.7" x2="34.29" y2="135.89" width="0.1524" layer="91"/>
<wire x1="34.29" y1="135.89" x2="74.93" y2="135.89" width="0.1524" layer="91"/>
<wire x1="74.93" y1="135.89" x2="95.25" y2="135.89" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="PB1"/>
<wire x1="40.64" y1="139.7" x2="34.29" y2="139.7" width="0.1524" layer="91"/>
<wire x1="109.22" y1="191.77" x2="95.25" y2="191.77" width="0.1524" layer="91"/>
</segment>
</net>
<net name="DISPLAY_DRIVER2" class="0">
<segment>
<pinref part="R25" gate="G$1" pin="P$2"/>
<wire x1="132.08" y1="177.8" x2="123.19" y2="177.8" width="0.1524" layer="91"/>
<label x="100.33" y="177.8" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="123.19" y1="204.47" x2="109.22" y2="204.47" width="0.1524" layer="91"/>
<wire x1="82.55" y1="204.47" x2="109.22" y2="204.47" width="0.1524" layer="91"/>
<label x="96.52" y="205.74" size="1.778" layer="95"/>
<pinref part="IC1" gate="G$1" pin="PB5"/>
<wire x1="40.64" y1="149.86" x2="24.13" y2="149.86" width="0.1524" layer="91"/>
<wire x1="24.13" y1="149.86" x2="24.13" y2="204.47" width="0.1524" layer="91"/>
<wire x1="24.13" y1="204.47" x2="29.21" y2="204.47" width="0.1524" layer="91"/>
<wire x1="29.21" y1="204.47" x2="82.55" y2="204.47" width="0.1524" layer="91"/>
</segment>
</net>
<net name="DISPLAY_DRIVER3" class="0">
<segment>
<pinref part="R26" gate="G$1" pin="P$2"/>
<wire x1="134.62" y1="175.26" x2="123.19" y2="175.26" width="0.1524" layer="91"/>
<label x="100.33" y="175.26" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="123.19" y1="210.82" x2="109.22" y2="210.82" width="0.1524" layer="91"/>
<wire x1="82.55" y1="210.82" x2="109.22" y2="210.82" width="0.1524" layer="91"/>
<label x="96.52" y="212.09" size="1.778" layer="95"/>
<wire x1="81.28" y1="210.82" x2="19.05" y2="210.82" width="0.1524" layer="91"/>
<wire x1="19.05" y1="210.82" x2="19.05" y2="209.55" width="0.1524" layer="91"/>
<wire x1="19.05" y1="142.24" x2="19.05" y2="204.47" width="0.1524" layer="91"/>
<wire x1="19.05" y1="209.55" x2="19.05" y2="204.47" width="0.1524" layer="91"/>
<wire x1="82.55" y1="210.82" x2="81.28" y2="210.82" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="PB2"/>
<wire x1="40.64" y1="142.24" x2="19.05" y2="142.24" width="0.1524" layer="91"/>
</segment>
</net>
<net name="DISPLAY_DRIVER4" class="0">
<segment>
<pinref part="R21" gate="G$1" pin="P$2"/>
<wire x1="135.89" y1="172.72" x2="123.19" y2="172.72" width="0.1524" layer="91"/>
<label x="100.33" y="172.72" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="123.19" y1="217.17" x2="107.95" y2="217.17" width="0.1524" layer="91"/>
<wire x1="81.28" y1="217.17" x2="107.95" y2="217.17" width="0.1524" layer="91"/>
<label x="97.79" y="218.44" size="1.778" layer="95"/>
<pinref part="IC1" gate="G$1" pin="PA3"/>
<wire x1="60.96" y1="160.02" x2="67.31" y2="160.02" width="0.1524" layer="91"/>
<wire x1="67.31" y1="160.02" x2="67.31" y2="217.17" width="0.1524" layer="91"/>
<wire x1="67.31" y1="217.17" x2="69.85" y2="217.17" width="0.1524" layer="91"/>
<wire x1="69.85" y1="217.17" x2="81.28" y2="217.17" width="0.1524" layer="91"/>
</segment>
</net>
<net name="DISPLAY_DRIVER5" class="0">
<segment>
<pinref part="R22" gate="G$1" pin="P$2"/>
<wire x1="139.7" y1="170.18" x2="123.19" y2="170.18" width="0.1524" layer="91"/>
<label x="100.33" y="170.18" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="123.19" y1="223.52" x2="107.95" y2="223.52" width="0.1524" layer="91"/>
<wire x1="91.44" y1="223.52" x2="107.95" y2="223.52" width="0.1524" layer="91"/>
<label x="97.79" y="224.79" size="1.778" layer="95"/>
<wire x1="91.44" y1="223.52" x2="91.44" y2="144.78" width="0.1524" layer="91"/>
<wire x1="91.44" y1="144.78" x2="80.01" y2="144.78" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="PC1"/>
<wire x1="80.01" y1="144.78" x2="60.96" y2="144.78" width="0.1524" layer="91"/>
</segment>
</net>
<net name="DISPLAY_DRIVER6" class="0">
<segment>
<pinref part="R23" gate="G$1" pin="P$2"/>
<wire x1="140.97" y1="167.64" x2="123.19" y2="167.64" width="0.1524" layer="91"/>
<label x="100.33" y="167.64" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="123.19" y1="229.87" x2="107.95" y2="229.87" width="0.1524" layer="91"/>
<wire x1="87.63" y1="229.87" x2="107.95" y2="229.87" width="0.1524" layer="91"/>
<label x="97.79" y="231.14" size="1.778" layer="95"/>
<wire x1="87.63" y1="229.87" x2="87.63" y2="228.6" width="0.1524" layer="91"/>
<wire x1="87.63" y1="228.6" x2="87.63" y2="149.86" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="PC3"/>
<wire x1="87.63" y1="149.86" x2="78.74" y2="149.86" width="0.1524" layer="91"/>
<wire x1="78.74" y1="149.86" x2="60.96" y2="149.86" width="0.1524" layer="91"/>
</segment>
</net>
<net name="DIGIT0" class="0">
<segment>
<pinref part="7_SEG1" gate="G$1" pin="DIG1"/>
<wire x1="185.42" y1="213.36" x2="171.45" y2="213.36" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="140.97" y1="87.63" x2="157.48" y2="87.63" width="0.1524" layer="91"/>
<wire x1="157.48" y1="87.63" x2="171.45" y2="87.63" width="0.1524" layer="91"/>
<label x="153.67" y="88.9" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="111.76" y1="130.81" x2="123.19" y2="130.81" width="0.1524" layer="91"/>
<label x="113.03" y="130.81" size="1.778" layer="95"/>
<wire x1="-2.54" y1="132.08" x2="-2.54" y2="154.94" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="PA6"/>
<wire x1="-2.54" y1="154.94" x2="40.64" y2="154.94" width="0.1524" layer="91"/>
<wire x1="111.76" y1="130.81" x2="-2.54" y2="130.81" width="0.1524" layer="91"/>
<wire x1="-2.54" y1="130.81" x2="-2.54" y2="132.08" width="0.1524" layer="91"/>
</segment>
</net>
<net name="DIGIT1" class="0">
<segment>
<pinref part="7_SEG1" gate="G$1" pin="DIG2"/>
<wire x1="185.42" y1="205.74" x2="171.45" y2="205.74" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="161.29" y1="74.93" x2="171.45" y2="74.93" width="0.1524" layer="91"/>
<wire x1="140.97" y1="74.93" x2="161.29" y2="74.93" width="0.1524" layer="91"/>
<label x="153.67" y="76.2" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="123.19" y1="127" x2="120.65" y2="127" width="0.1524" layer="91"/>
<wire x1="110.49" y1="127" x2="120.65" y2="127" width="0.1524" layer="91"/>
<label x="113.03" y="128.27" size="1.778" layer="95"/>
<wire x1="100.33" y1="127" x2="0" y2="127" width="0.1524" layer="91"/>
<wire x1="0" y1="127" x2="0" y2="152.4" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="PA7"/>
<wire x1="0" y1="152.4" x2="40.64" y2="152.4" width="0.1524" layer="91"/>
<wire x1="110.49" y1="127" x2="100.33" y2="127" width="0.1524" layer="91"/>
</segment>
</net>
<net name="DIGIT2" class="0">
<segment>
<pinref part="7_SEG1" gate="G$1" pin="DIG3"/>
<wire x1="185.42" y1="203.2" x2="171.45" y2="203.2" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="140.97" y1="67.31" x2="152.4" y2="67.31" width="0.1524" layer="91"/>
<wire x1="152.4" y1="67.31" x2="171.45" y2="67.31" width="0.1524" layer="91"/>
<label x="153.67" y="68.58" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="123.19" y1="121.92" x2="120.65" y2="121.92" width="0.1524" layer="91"/>
<wire x1="110.49" y1="121.92" x2="120.65" y2="121.92" width="0.1524" layer="91"/>
<label x="113.03" y="123.19" size="1.778" layer="95"/>
<wire x1="104.14" y1="121.92" x2="102.87" y2="121.92" width="0.1524" layer="91"/>
<wire x1="102.87" y1="121.92" x2="83.82" y2="121.92" width="0.1524" layer="91"/>
<wire x1="83.82" y1="121.92" x2="2.54" y2="121.92" width="0.1524" layer="91"/>
<wire x1="2.54" y1="121.92" x2="2.54" y2="147.32" width="0.1524" layer="91"/>
<wire x1="2.54" y1="147.32" x2="33.02" y2="147.32" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="PB4"/>
<wire x1="33.02" y1="147.32" x2="40.64" y2="147.32" width="0.1524" layer="91"/>
<wire x1="104.14" y1="121.92" x2="110.49" y2="121.92" width="0.1524" layer="91"/>
</segment>
</net>
<net name="DIGIT3" class="0">
<segment>
<pinref part="7_SEG1" gate="G$1" pin="DIG4"/>
<wire x1="185.42" y1="198.12" x2="171.45" y2="198.12" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="161.29" y1="55.88" x2="171.45" y2="55.88" width="0.1524" layer="91"/>
<wire x1="140.97" y1="55.88" x2="161.29" y2="55.88" width="0.1524" layer="91"/>
<label x="153.67" y="57.15" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="123.19" y1="116.84" x2="97.79" y2="116.84" width="0.1524" layer="91"/>
<wire x1="85.09" y1="116.84" x2="97.79" y2="116.84" width="0.1524" layer="91"/>
<label x="114.3" y="118.11" size="1.778" layer="95"/>
<wire x1="85.09" y1="116.84" x2="13.97" y2="116.84" width="0.1524" layer="91"/>
<wire x1="13.97" y1="116.84" x2="13.97" y2="157.48" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="PA5"/>
<wire x1="13.97" y1="157.48" x2="40.64" y2="157.48" width="0.1524" layer="91"/>
</segment>
</net>
<net name="DIGIT4" class="0">
<segment>
<pinref part="7_SEG2" gate="G$1" pin="DIG1"/>
<wire x1="185.42" y1="166.37" x2="171.45" y2="166.37" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="160.02" y1="125.73" x2="171.45" y2="125.73" width="0.1524" layer="91"/>
<wire x1="140.97" y1="125.73" x2="160.02" y2="125.73" width="0.1524" layer="91"/>
<label x="151.13" y="127" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="123.19" y1="113.03" x2="97.79" y2="113.03" width="0.1524" layer="91"/>
<label x="113.03" y="113.03" size="1.778" layer="95"/>
<pinref part="IC1" gate="G$1" pin="PB0"/>
<wire x1="60.96" y1="139.7" x2="78.74" y2="139.7" width="0.1524" layer="91"/>
<wire x1="78.74" y1="139.7" x2="78.74" y2="113.03" width="0.1524" layer="91"/>
<wire x1="78.74" y1="113.03" x2="97.79" y2="113.03" width="0.1524" layer="91"/>
</segment>
</net>
<net name="DIGIT5" class="0">
<segment>
<pinref part="7_SEG2" gate="G$1" pin="DIG2"/>
<wire x1="185.42" y1="158.75" x2="171.45" y2="158.75" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="165.1" y1="116.84" x2="171.45" y2="116.84" width="0.1524" layer="91"/>
<wire x1="140.97" y1="116.84" x2="165.1" y2="116.84" width="0.1524" layer="91"/>
<label x="151.13" y="118.11" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="123.19" y1="109.22" x2="97.79" y2="109.22" width="0.1524" layer="91"/>
<wire x1="85.09" y1="109.22" x2="97.79" y2="109.22" width="0.1524" layer="91"/>
<label x="111.76" y="109.22" size="1.778" layer="95"/>
<pinref part="IC1" gate="G$1" pin="PC0"/>
<wire x1="60.96" y1="142.24" x2="82.55" y2="142.24" width="0.1524" layer="91"/>
<wire x1="82.55" y1="142.24" x2="82.55" y2="109.22" width="0.1524" layer="91"/>
<wire x1="85.09" y1="109.22" x2="82.55" y2="109.22" width="0.1524" layer="91"/>
</segment>
</net>
<net name="DIGIT6" class="0">
<segment>
<pinref part="7_SEG2" gate="G$1" pin="DIG3"/>
<wire x1="185.42" y1="156.21" x2="171.45" y2="156.21" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="171.45" y1="62.23" x2="171.45" y2="60.96" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="163.83" y1="110.49" x2="171.45" y2="110.49" width="0.1524" layer="91"/>
<wire x1="140.97" y1="110.49" x2="163.83" y2="110.49" width="0.1524" layer="91"/>
<label x="152.4" y="111.76" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="123.19" y1="105.41" x2="96.52" y2="105.41" width="0.1524" layer="91"/>
<label x="111.76" y="105.41" size="1.778" layer="95"/>
<pinref part="IC1" gate="G$1" pin="PC2"/>
<wire x1="60.96" y1="147.32" x2="86.36" y2="147.32" width="0.1524" layer="91"/>
<wire x1="86.36" y1="147.32" x2="86.36" y2="105.41" width="0.1524" layer="91"/>
<wire x1="96.52" y1="105.41" x2="86.36" y2="105.41" width="0.1524" layer="91"/>
</segment>
</net>
<net name="DIGIT7" class="0">
<segment>
<pinref part="7_SEG2" gate="G$1" pin="DIG4"/>
<wire x1="185.42" y1="151.13" x2="171.45" y2="151.13" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="158.75" y1="97.79" x2="171.45" y2="97.79" width="0.1524" layer="91"/>
<wire x1="140.97" y1="97.79" x2="158.75" y2="97.79" width="0.1524" layer="91"/>
<label x="153.67" y="99.06" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="123.19" y1="101.6" x2="96.52" y2="101.6" width="0.1524" layer="91"/>
<wire x1="85.09" y1="101.6" x2="96.52" y2="101.6" width="0.1524" layer="91"/>
<label x="113.03" y="101.6" size="1.778" layer="95"/>
<pinref part="IC1" gate="G$1" pin="PA1"/>
<wire x1="60.96" y1="154.94" x2="73.66" y2="154.94" width="0.1524" layer="91"/>
<wire x1="73.66" y1="154.94" x2="73.66" y2="101.6" width="0.1524" layer="91"/>
<wire x1="85.09" y1="101.6" x2="73.66" y2="101.6" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$40" class="0">
<segment>
<wire x1="-107.95" y1="137.16" x2="-86.36" y2="137.16" width="0.1524" layer="91"/>
<wire x1="-86.36" y1="137.16" x2="-86.36" y2="129.54" width="0.1524" layer="91"/>
<wire x1="-86.36" y1="129.54" x2="-71.12" y2="129.54" width="0.1524" layer="91"/>
<wire x1="-71.12" y1="129.54" x2="-8.89" y2="129.54" width="0.1524" layer="91"/>
<pinref part="R3" gate="G$1" pin="P$1"/>
<wire x1="-107.95" y1="137.16" x2="-107.95" y2="147.32" width="0.1524" layer="91"/>
<pinref part="IC2" gate="G$1" pin="PD0(RXD)"/>
<wire x1="19.05" y1="45.72" x2="31.75" y2="45.72" width="0.1524" layer="91"/>
<wire x1="31.75" y1="45.72" x2="31.75" y2="82.55" width="0.1524" layer="91"/>
<wire x1="31.75" y1="82.55" x2="-8.89" y2="82.55" width="0.1524" layer="91"/>
<wire x1="-8.89" y1="82.55" x2="-8.89" y2="129.54" width="0.1524" layer="91"/>
<pinref part="Q1" gate="G$1" pin="D"/>
<wire x1="-110.49" y1="137.16" x2="-107.95" y2="137.16" width="0.1524" layer="91"/>
<junction x="-107.95" y="137.16"/>
</segment>
</net>
<net name="N$15" class="0">
<segment>
<pinref part="R2" gate="G$1" pin="P$1"/>
<wire x1="-124.46" y1="137.16" x2="-124.46" y2="138.43" width="0.1524" layer="91"/>
<wire x1="-124.46" y1="137.16" x2="-124.46" y2="134.62" width="0.1524" layer="91"/>
<wire x1="-124.46" y1="134.62" x2="-124.46" y2="124.46" width="0.1524" layer="91"/>
<wire x1="-124.46" y1="124.46" x2="-71.12" y2="124.46" width="0.1524" layer="91"/>
<wire x1="-71.12" y1="124.46" x2="-71.12" y2="96.52" width="0.1524" layer="91"/>
<pinref part="Q1" gate="G$1" pin="S"/>
<wire x1="-120.65" y1="137.16" x2="-124.46" y2="137.16" width="0.1524" layer="91"/>
<junction x="-124.46" y="137.16"/>
<pinref part="MOD1" gate="G$1" pin="TXO"/>
<wire x1="-91.44" y1="96.52" x2="-71.12" y2="96.52" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="SW4" gate="G$1" pin="2"/>
<pinref part="R27" gate="G$1" pin="P$2"/>
<wire x1="143.51" y1="26.67" x2="143.51" y2="31.75" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="SW3" gate="G$1" pin="2"/>
<pinref part="R19" gate="G$1" pin="P$2"/>
<wire x1="119.38" y1="27.94" x2="119.38" y2="30.48" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$11" class="0">
<segment>
<pinref part="C17" gate="G$1" pin="2"/>
<pinref part="R28" gate="G$1" pin="P$1"/>
<wire x1="166.37" y1="31.75" x2="154.94" y2="31.75" width="0.1524" layer="91"/>
<wire x1="154.94" y1="31.75" x2="154.94" y2="19.05" width="0.1524" layer="91"/>
<pinref part="IC2" gate="G$1" pin="PD7(AIN1)"/>
<wire x1="19.05" y1="27.94" x2="78.74" y2="27.94" width="0.1524" layer="91"/>
<wire x1="78.74" y1="27.94" x2="78.74" y2="39.37" width="0.1524" layer="91"/>
<wire x1="78.74" y1="39.37" x2="154.94" y2="39.37" width="0.1524" layer="91"/>
<wire x1="154.94" y1="39.37" x2="154.94" y2="31.75" width="0.1524" layer="91"/>
<junction x="154.94" y="31.75"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="LED1" gate="G$1" pin="1"/>
<pinref part="R15" gate="G$1" pin="P$1"/>
<wire x1="71.12" y1="41.91" x2="69.85" y2="41.91" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="LED1" gate="G$1" pin="3"/>
<pinref part="R16" gate="G$1" pin="P$2"/>
<wire x1="68.58" y1="49.53" x2="71.12" y2="49.53" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$16" class="0">
<segment>
<pinref part="SW5" gate="G$1" pin="2"/>
<pinref part="R28" gate="G$1" pin="P$2"/>
<wire x1="176.53" y1="26.67" x2="176.53" y2="31.75" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$19" class="0">
<segment>
<pinref part="R27" gate="G$1" pin="P$1"/>
<wire x1="133.35" y1="31.75" x2="130.81" y2="31.75" width="0.1524" layer="91"/>
<pinref part="C16" gate="G$1" pin="2"/>
<wire x1="130.81" y1="31.75" x2="130.81" y2="19.05" width="0.1524" layer="91"/>
<wire x1="125.73" y1="1.27" x2="125.73" y2="31.75" width="0.1524" layer="91"/>
<wire x1="125.73" y1="31.75" x2="130.81" y2="31.75" width="0.1524" layer="91"/>
<junction x="130.81" y="31.75"/>
<wire x1="83.82" y1="33.02" x2="83.82" y2="5.08" width="0.1524" layer="91"/>
<wire x1="83.82" y1="5.08" x2="83.82" y2="1.27" width="0.1524" layer="91"/>
<wire x1="83.82" y1="1.27" x2="125.73" y2="1.27" width="0.1524" layer="91"/>
<wire x1="83.82" y1="33.02" x2="38.1" y2="33.02" width="0.1524" layer="91"/>
<pinref part="IC2" gate="G$1" pin="PD5(T1)"/>
<wire x1="33.02" y1="33.02" x2="19.05" y2="33.02" width="0.1524" layer="91"/>
<wire x1="38.1" y1="33.02" x2="33.02" y2="33.02" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="IC2" gate="G$1" pin="PB1(OC1A)"/>
<wire x1="19.05" y1="20.32" x2="55.88" y2="20.32" width="0.1524" layer="91"/>
<wire x1="55.88" y1="20.32" x2="55.88" y2="41.91" width="0.1524" layer="91"/>
<pinref part="R15" gate="G$1" pin="P$2"/>
<wire x1="55.88" y1="41.91" x2="59.69" y2="41.91" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$1" class="0">
<segment>
<pinref part="IC2" gate="G$1" pin="PB0(ICP)"/>
<wire x1="19.05" y1="22.86" x2="53.34" y2="22.86" width="0.1524" layer="91"/>
<wire x1="53.34" y1="22.86" x2="53.34" y2="49.53" width="0.1524" layer="91"/>
<pinref part="R16" gate="G$1" pin="P$1"/>
<wire x1="53.34" y1="49.53" x2="58.42" y2="49.53" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$18" class="0">
<segment>
<pinref part="R2" gate="G$1" pin="P$2"/>
<wire x1="-118.11" y1="151.13" x2="-124.46" y2="151.13" width="0.1524" layer="91"/>
<wire x1="-124.46" y1="151.13" x2="-124.46" y2="148.59" width="0.1524" layer="91"/>
<wire x1="-124.46" y1="151.13" x2="-133.35" y2="151.13" width="0.1524" layer="91"/>
<wire x1="-133.35" y1="151.13" x2="-133.35" y2="114.3" width="0.1524" layer="91"/>
<junction x="-124.46" y="151.13"/>
<wire x1="-133.35" y1="114.3" x2="-78.74" y2="114.3" width="0.1524" layer="91"/>
<wire x1="-78.74" y1="114.3" x2="-78.74" y2="104.14" width="0.1524" layer="91"/>
<pinref part="Q1" gate="G$1" pin="G"/>
<wire x1="-118.11" y1="151.13" x2="-118.11" y2="142.24" width="0.1524" layer="91"/>
<pinref part="MOD1" gate="G$1" pin="3V3"/>
<wire x1="-91.44" y1="104.14" x2="-78.74" y2="104.14" width="0.1524" layer="91"/>
</segment>
</net>
<net name="SEVEN_SEG7" class="0">
<segment>
<pinref part="R1" gate="G$1" pin="P$1"/>
<wire x1="153.67" y1="165.1" x2="154.94" y2="165.1" width="0.1524" layer="91"/>
<wire x1="154.94" y1="165.1" x2="158.75" y2="165.1" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="7_SEG1" gate="G$1" pin="CLON"/>
<wire x1="185.42" y1="190.5" x2="158.75" y2="190.5" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="7_SEG2" gate="G$1" pin="CLON"/>
<wire x1="185.42" y1="143.51" x2="158.75" y2="143.51" width="0.1524" layer="91"/>
</segment>
</net>
<net name="DISPLAY_DRIVER7" class="0">
<segment>
<pinref part="R1" gate="G$1" pin="P$2"/>
<wire x1="143.51" y1="165.1" x2="123.19" y2="165.1" width="0.1524" layer="91"/>
<label x="100.33" y="165.1" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="123.19" y1="236.22" x2="95.25" y2="236.22" width="0.1524" layer="91"/>
<wire x1="81.28" y1="236.22" x2="95.25" y2="236.22" width="0.1524" layer="91"/>
<label x="97.79" y="237.49" size="1.778" layer="95"/>
<wire x1="81.28" y1="236.22" x2="21.59" y2="236.22" width="0.1524" layer="91"/>
<wire x1="21.59" y1="236.22" x2="21.59" y2="144.78" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="PB3"/>
<wire x1="21.59" y1="144.78" x2="40.64" y2="144.78" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<wire x1="76.2" y1="17.78" x2="76.2" y2="24.13" width="0.1524" layer="91"/>
<wire x1="76.2" y1="24.13" x2="76.2" y2="25.4" width="0.1524" layer="91"/>
<wire x1="76.2" y1="25.4" x2="92.71" y2="25.4" width="0.1524" layer="91"/>
<pinref part="SW1" gate="G$1" pin="2"/>
<wire x1="92.71" y1="25.4" x2="92.71" y2="24.13" width="0.1524" layer="91"/>
<wire x1="76.2" y1="17.78" x2="41.91" y2="17.78" width="0.1524" layer="91"/>
<wire x1="41.91" y1="17.78" x2="41.91" y2="40.64" width="0.1524" layer="91"/>
<wire x1="41.91" y1="40.64" x2="41.91" y2="55.88" width="0.1524" layer="91"/>
<pinref part="IC2" gate="G$1" pin="PC5(ADC5/SCL)"/>
<wire x1="41.91" y1="55.88" x2="19.05" y2="55.88" width="0.1524" layer="91"/>
</segment>
</net>
<net name="DISPLAY_DRIVER1" class="0">
<segment>
<wire x1="123.19" y1="180.34" x2="127" y2="180.34" width="0.1524" layer="91"/>
<pinref part="R20" gate="G$1" pin="P$1"/>
<wire x1="127" y1="180.34" x2="129.54" y2="180.34" width="0.1524" layer="91"/>
<label x="100.33" y="180.34" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="123.19" y1="198.12" x2="109.22" y2="198.12" width="0.1524" layer="91"/>
<wire x1="82.55" y1="198.12" x2="109.22" y2="198.12" width="0.1524" layer="91"/>
<label x="96.52" y="199.39" size="1.778" layer="95"/>
<wire x1="16.51" y1="191.77" x2="16.51" y2="198.12" width="0.1524" layer="91"/>
<wire x1="16.51" y1="198.12" x2="69.85" y2="198.12" width="0.1524" layer="91"/>
<wire x1="69.85" y1="198.12" x2="72.39" y2="198.12" width="0.1524" layer="91"/>
<wire x1="72.39" y1="198.12" x2="82.55" y2="198.12" width="0.1524" layer="91"/>
<wire x1="16.51" y1="191.77" x2="16.51" y2="160.02" width="0.1524" layer="91"/>
<wire x1="16.51" y1="160.02" x2="29.21" y2="160.02" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="PA4"/>
<wire x1="29.21" y1="160.02" x2="40.64" y2="160.02" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$9" class="0">
<segment>
<wire x1="45.72" y1="36.83" x2="83.82" y2="36.83" width="0.1524" layer="91"/>
<wire x1="83.82" y1="36.83" x2="107.95" y2="36.83" width="0.1524" layer="91"/>
<pinref part="C15" gate="G$1" pin="2"/>
<pinref part="R19" gate="G$1" pin="P$1"/>
<wire x1="109.22" y1="30.48" x2="107.95" y2="30.48" width="0.1524" layer="91"/>
<wire x1="107.95" y1="30.48" x2="107.95" y2="22.86" width="0.1524" layer="91"/>
<wire x1="107.95" y1="36.83" x2="107.95" y2="30.48" width="0.1524" layer="91"/>
<junction x="107.95" y="30.48"/>
<wire x1="45.72" y1="36.83" x2="44.45" y2="36.83" width="0.1524" layer="91"/>
<pinref part="IC2" gate="G$1" pin="PD2(INT0)"/>
<wire x1="19.05" y1="40.64" x2="36.83" y2="40.64" width="0.1524" layer="91"/>
<wire x1="36.83" y1="40.64" x2="36.83" y2="36.83" width="0.1524" layer="91"/>
<wire x1="36.83" y1="36.83" x2="44.45" y2="36.83" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="RST"/>
<wire x1="60.96" y1="152.4" x2="64.77" y2="152.4" width="0.1524" layer="91"/>
<wire x1="64.77" y1="152.4" x2="64.77" y2="59.69" width="0.1524" layer="91"/>
<wire x1="48.26" y1="59.69" x2="48.26" y2="15.24" width="0.1524" layer="91"/>
<wire x1="48.26" y1="15.24" x2="22.86" y2="15.24" width="0.1524" layer="91"/>
<pinref part="IC2" gate="G$1" pin="PB3(MOSI/OC2)"/>
<wire x1="19.05" y1="15.24" x2="22.86" y2="15.24" width="0.1524" layer="91"/>
<wire x1="64.77" y1="59.69" x2="48.26" y2="59.69" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$10" class="0">
<segment>
<wire x1="69.85" y1="157.48" x2="69.85" y2="57.15" width="0.1524" layer="91"/>
<wire x1="69.85" y1="57.15" x2="50.8" y2="57.15" width="0.1524" layer="91"/>
<wire x1="50.8" y1="57.15" x2="50.8" y2="12.7" width="0.1524" layer="91"/>
<wire x1="50.8" y1="12.7" x2="21.59" y2="12.7" width="0.1524" layer="91"/>
<pinref part="IC2" gate="G$1" pin="PB4(MISO)"/>
<wire x1="19.05" y1="12.7" x2="21.59" y2="12.7" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="PA2"/>
<wire x1="60.96" y1="157.48" x2="66.04" y2="157.48" width="0.1524" layer="91"/>
<wire x1="66.04" y1="157.48" x2="69.85" y2="157.48" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$12" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="P$1"/>
<wire x1="-50.8" y1="44.45" x2="-35.56" y2="44.45" width="0.1524" layer="91"/>
<wire x1="-35.56" y1="44.45" x2="-35.56" y2="48.26" width="0.1524" layer="91"/>
<pinref part="IC2" gate="G$1" pin="PB6(XTAL1/TOSC1)"/>
<wire x1="-29.21" y1="50.8" x2="-30.48" y2="50.8" width="0.1524" layer="91"/>
<wire x1="-30.48" y1="50.8" x2="-30.48" y2="48.26" width="0.1524" layer="91"/>
<wire x1="-30.48" y1="48.26" x2="-35.56" y2="48.26" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$17" class="0">
<segment>
<pinref part="IC2" gate="G$1" pin="PB7(XTAL2/TOSC2)"/>
<wire x1="-29.21" y1="45.72" x2="-31.75" y2="45.72" width="0.1524" layer="91"/>
<wire x1="-31.75" y1="45.72" x2="-31.75" y2="40.64" width="0.1524" layer="91"/>
<wire x1="-31.75" y1="40.64" x2="-45.72" y2="40.64" width="0.1524" layer="91"/>
<wire x1="-45.72" y1="40.64" x2="-45.72" y2="41.91" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="P$2"/>
<wire x1="-45.72" y1="41.91" x2="-50.8" y2="41.91" width="0.1524" layer="91"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports URNs for individual library
assets (packages, symbols, and devices). The URNs of those assets
will not be understood (or retained) with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports the association of 3D packages
with devices in libraries, schematics, and board files. Those 3D
packages will not be understood (or retained) with this version.
</note>
</compatibility>
</eagle>
