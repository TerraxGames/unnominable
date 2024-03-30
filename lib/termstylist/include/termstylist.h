/*
 * TermStylist - A header-only terminal colours library.
 * By @alexwkleung on GitHub
 * https://github.com/alexwkleung/TermStylist
 * MIT License.
 */

#ifndef TERMSTYLIST_H
#define TERMSTYLIST_H

#include <ostream>
#include <string>

namespace termstylist {
  //attributes
  struct Attributes {
  public:
    const std::string ATTRS_Bold = "\033[1m"; //1
    const std::string ATTRS_Dim = "\033[2m"; //2
    const std::string ATTRS_Underline = "\033[4m"; //4
    const std::string ATTRS_Reverse = "\033[7m"; //7
    const std::string ATTRS_Clear = "\033c"; //c
  };

  //reset
  struct Reset {
  public:
    const std::string RESET_Default = "\033[0m"; //0
    const std::string RESET_Dim = "\033[22m"; //22
    const std::string RESET_Bold = "\033[21m"; //21
    const std::string RESET_Underline = "\033[24m"; //24
    const std::string RESET_Reverse = "\033[27m"; //27
  };

  //foreground colours - 8/16 colours (normal, light, bold)
  struct FGColours816 {
  public:
    //8 colours
    const std::string FG_Default = "\033[39m"; //39
    const std::string FG_Black = "\033[30m"; //30
    const std::string FG_Red = "\033[31m"; //31
    const std::string FG_Green = "\033[32m"; //32
    const std::string FG_Yellow = "\033[33m"; //33
    const std::string FG_Blue = "\033[34m"; //34
    const std::string FG_Magenta = "\033[35m"; //35
    const std::string FG_Cyan = "\033[36m"; //36
    const std::string FG_White = "\033[97m"; //97
    const std::string FG_LightGrey = "\033[37m"; //37
    const std::string FG_DarkGrey = "\033[90m"; //90
    const std::string FG_LightRed = "\033[91m"; //91
    const std::string FG_LightGreen = "\033[92m"; //92
    const std::string FG_LightYellow = "\033[93m"; //93
    const std::string FG_LightBlue = "\033[94m"; //94
    const std::string FG_LightMagenta = "\033[95m"; //95
    const std::string FG_LightCyan = "\033[96m"; //96

    //16 colours
    const std::string FG_BoldBlack = "\033[30;1m"; //30;1
    const std::string FG_BoldRed = "\033[31;1m"; //31;1
    const std::string FG_BoldGreen = "\033[32;1m"; //32;1
    const std::string FG_BoldYellow = "\033[33;1m"; //33;1
    const std::string FG_BoldBlue = "\033[34;1m"; //34;1
    const std::string FG_BoldMagenta = "\033[35;1m"; //35;1
    const std::string FG_BoldCyan = "\033[36;1m"; //36;1
    const std::string FG_BoldWhite = "\033[97;1m"; //97;1
    const std::string FG_BoldLightGrey = "\033[37;1m"; //37;1
    const std::string FG_BoldDarkGrey = "\033[90;1m"; //90;1
    const std::string FG_BoldLightRed = "\033[91;1m"; //91;1
    const std::string FG_BoldLightGreen = "\033[92;1m"; //92;1
    const std::string FG_BoldLightYellow = "\033[93;1m"; //93;1
    const std::string FG_BoldLightBlue = "\033[94;1m"; //94;1
    const std::string FG_BoldLightMagenta = "\033[95;1m"; //95;1
    const std::string FG_BoldLightCyan = "\033[96;1m"; //96;1
  };

  //background colours - 8/16 colours (normal, light, bold)
  struct BGColours816 {
  public:
    //8 colours
    const std::string BG_Default = "\033[49m"; //49
    const std::string BG_Black = "\033[40m"; //40
    const std::string BG_Red = "\033[41m"; //41
    const std::string BG_Green = "\033[42m"; //42
    const std::string BG_Yellow = "\033[43m"; //43
    const std::string BG_Blue = "\033[44m"; //44
    const std::string BG_Magenta = "\033[45m"; //45
    const std::string BG_Cyan = "\033[46m"; //46
    const std::string BG_White = "\033[107m"; //107
    const std::string BG_LightGrey = "\033[47m"; //47
    const std::string BG_DarkGrey = "\033[100m"; //100
    const std::string BG_LightRed = "\033[101m"; //101
    const std::string BG_LightGreen = "\033[102m"; //102 
    const std::string BG_LightYellow = "\033[103m"; //103
    const std::string BG_LightBlue = "\033[104m"; //104
    const std::string BG_LightMagenta = "\033[105m"; //105
    const std::string BG_LightCyan = "\033[106m"; //106

    //16 colours
    const std::string BG_BoldBlack = "\033[40;1m"; //40;1
    const std::string BG_BoldRed = "\033[41;1m"; //41;1
    const std::string BG_BoldGreen = "\033[42;1m"; //42;1
    const std::string BG_BoldYellow = "\033[43;1m"; //43;1
    const std::string BG_BoldBlue = "\033[44;1m"; //44;1
    const std::string BG_BoldMagenta = "\033[45;1m"; //45;1
    const std::string BG_BoldCyan = "\033[46;1m"; //46;1
    const std::string BG_BoldWhite = "\033[107;1m"; //107;1
    const std::string BG_BoldLightGrey = "\033[47;1m"; //47;1
    const std::string BG_BoldDarkGrey = "\033[100;1m"; //100;1
    const std::string BG_BoldLightRed = "\033[101;1m"; //101;1
    const std::string BG_BoldLightGreen = "\033[102;1m"; //102;1
    const std::string BG_BoldLightYellow = "\033[103;1m"; //103;1
    const std::string BG_BoldLightBlue = "\033[104;1m"; //104;1
    const std::string BG_BoldLightMagenta = "\033[105;1m"; //105;1
    const std::string BG_BoldLightCyan = "\033[106;1m"; //106;1
  };

  //foreground colours - 256 colours 
  struct FGColours256 {
  public:
    const std::string FG256_0 = "\033[38;5;0m"; //38;5;0
    const std::string FG256_1 = "\033[38;5;1m"; //38;5;1
    const std::string FG256_2 = "\033[38;5;2m"; //38;5;2
    const std::string FG256_3 = "\033[38;5;3m"; //38;5;3
    const std::string FG256_4 = "\033[38;5;4m"; //38;5;4
    const std::string FG256_5 = "\033[38;5;5m"; //38;5;5
    const std::string FG256_6 = "\033[38;5;6m"; //38;5;6
    const std::string FG256_7 = "\033[38;5;7m"; //38;5;7
    const std::string FG256_8 = "\033[38;5;8m"; //38;5;8
    const std::string FG256_9 = "\033[38;5;9m"; //38;5;9
    const std::string FG256_10 = "\033[38;5;10m"; //38;5;10
    const std::string FG256_11 = "\033[38;5;11m"; //38;5;11
    const std::string FG256_12 = "\033[38;5;12m"; //38;5;12
    const std::string FG256_13 = "\033[38;5;13m"; //38;5;13
    const std::string FG256_14 = "\033[38;5;14m"; //38;5;14
    const std::string FG256_15 = "\033[38;5;15m"; //38;5;15
    const std::string FG256_16 = "\033[38;5;16m"; //38;5;16
    const std::string FG256_17 = "\033[38;5;17m"; //38;5;17
    const std::string FG256_18 = "\033[38;5;18m"; //38;5;18
    const std::string FG256_19 = "\033[38;5;19m"; //38;5;19
    const std::string FG256_20 = "\033[38;5;20m"; //38;5;20
    const std::string FG256_21 = "\033[38;5;21m"; //38;5;21
    const std::string FG256_22 = "\033[38;5;22m"; //38;5;22
    const std::string FG256_23 = "\033[38;5;23m"; //38;5;23
    const std::string FG256_24 = "\033[38;5;24m"; //38;5;24
    const std::string FG256_25 = "\033[38;5;25m"; //38;5;25
    const std::string FG256_26 = "\033[38;5;26m"; //38;5;26
    const std::string FG256_27 = "\033[38;5;27m"; //38;5;27
    const std::string FG256_28 = "\033[38;5;28m"; //38;5;28
    const std::string FG256_29 = "\033[38;5;29m"; //38;5;29
    const std::string FG256_30 = "\033[38;5;30m"; //38;5;30
    const std::string FG256_31 = "\033[38;5;31m"; //38;5;31
    const std::string FG256_32 = "\033[38;5;32m"; //38;5;32
    const std::string FG256_33 = "\033[38;5;33m"; //38;5;33
    const std::string FG256_34 = "\033[38;5;34m"; //38;5;34
    const std::string FG256_35 = "\033[38;5;35m"; //38;5;35
    const std::string FG256_36 = "\033[38;5;36m"; //38;5;36
    const std::string FG256_37 = "\033[38;5;37m"; //38;5;37
    const std::string FG256_38 = "\033[38;5;38m"; //38;5;38
    const std::string FG256_39 = "\033[38;5;39m"; //38;5;39
    const std::string FG256_40 = "\033[38;5;40m"; //38;5;40
    const std::string FG256_41 = "\033[38;5;41m"; //38;5;41
    const std::string FG256_42 = "\033[38;5;42m"; //38;5;42
    const std::string FG256_43 = "\033[38;5;43m"; //38;5;43
    const std::string FG256_44 = "\033[38;5;44m"; //38;5;44
    const std::string FG256_45 = "\033[38;5;45m"; //38;5;45
    const std::string FG256_46 = "\033[38;5;46m"; //38;5;46
    const std::string FG256_47 = "\033[38;5;47m"; //38;5;47
    const std::string FG256_48 = "\033[38;5;48m"; //38;5;48
    const std::string FG256_49 = "\033[38;5;49m"; //38;5;49
    const std::string FG256_50 = "\033[38;5;50m"; //38;5;50
    const std::string FG256_51 = "\033[38;5;51m"; //38;5;51
    const std::string FG256_52 = "\033[38;5;52m"; //38;5;52
    const std::string FG256_53 = "\033[38;5;53m"; //38;5;53
    const std::string FG256_54 = "\033[38;5;54m"; //38;5;54
    const std::string FG256_55 = "\033[38;5;55m"; //38;5;55
    const std::string FG256_56 = "\033[38;5;56m"; //38;5;56
    const std::string FG256_57 = "\033[38;5;57m"; //38;5;57
    const std::string FG256_58 = "\033[38;5;58m"; //38;5;58
    const std::string FG256_59 = "\033[38;5;59m"; //38;5;59
    const std::string FG256_60 = "\033[38;5;60m"; //38;5;60
    const std::string FG256_61 = "\033[38;5;61m"; //38;5;61
    const std::string FG256_62 = "\033[38;5;62m"; //38;5;62
    const std::string FG256_63 = "\033[38;5;63m"; //38;5;63
    const std::string FG256_64 = "\033[38;5;64m"; //38;5;64
    const std::string FG256_65 = "\033[38;5;65m"; //38;5;65
    const std::string FG256_66 = "\033[38;5;66m"; //38;5;66
    const std::string FG256_67 = "\033[38;5;67m"; //38;5;67
    const std::string FG256_68 = "\033[38;5;68m"; //38;5;68
    const std::string FG256_69 = "\033[38;5;69m"; //38;5;69
    const std::string FG256_70 = "\033[38;5;70m"; //38;5;70
    const std::string FG256_71 = "\033[38;5;71m"; //38;5;71
    const std::string FG256_72 = "\033[38;5;72m"; //38;5;72
    const std::string FG256_73 = "\033[38;5;73m"; //38;5;73
    const std::string FG256_74 = "\033[38;5;74m"; //38;5;74
    const std::string FG256_75 = "\033[38;5;75m"; //38;5;75
    const std::string FG256_76 = "\033[38;5;76m"; //38;5;76
    const std::string FG256_77 = "\033[38;5;77m"; //38;5;77
    const std::string FG256_78 = "\033[38;5;78m"; //38;5;78
    const std::string FG256_79 = "\033[38;5;79m"; //38;5;79
    const std::string FG256_80 = "\033[38;5;80m"; //38;5;80
    const std::string FG256_81 = "\033[38;5;81m"; //38;5;81
    const std::string FG256_82 = "\033[38;5;82m"; //38;5;82
    const std::string FG256_83 = "\033[38;5;83m"; //38;5;83
    const std::string FG256_84 = "\033[38;5;84m"; //38;5;84
    const std::string FG256_85 = "\033[38;5;85m"; //38;5;85
    const std::string FG256_86 = "\033[38;5;86m"; //38;5;86
    const std::string FG256_87 = "\033[38;5;87m"; //38;5;87
    const std::string FG256_88 = "\033[38;5;88m"; //38;5;88
    const std::string FG256_89 = "\033[38;5;89m"; //38;5;89
    const std::string FG256_90 = "\033[38;5;90m"; //38;5;90
    const std::string FG256_91 = "\033[38;5;91m"; //38;5;91
    const std::string FG256_92 = "\033[38;5;92m"; //38;5;92
    const std::string FG256_93 = "\033[38;5;93m"; //38;5;93
    const std::string FG256_94 = "\033[38;5;94m"; //38;5;94
    const std::string FG256_95 = "\033[38;5;95m"; //38;5;95
    const std::string FG256_96 = "\033[38;5;96m"; //38;5;96
    const std::string FG256_97 = "\033[38;5;97m"; //38;5;97
    const std::string FG256_98 = "\033[38;5;98m"; //38;5;98
    const std::string FG256_99 = "\033[38;5;99m"; //38;5;99
    const std::string FG256_100 = "\033[38;5;100m"; //38;5;100
    const std::string FG256_101 = "\033[38;5;101m"; //38;5;101
    const std::string FG256_102 = "\033[38;5;102m"; //38;5;102
    const std::string FG256_103 = "\033[38;5;103m"; //38;5;103
    const std::string FG256_104 = "\033[38;5;104m"; //38;5;104
    const std::string FG256_105 = "\033[38;5;105m"; //38;5;105 
    const std::string FG256_106 = "\033[38;5;106m"; //38;5;106
    const std::string FG256_107 = "\033[38;5;107m"; //38;5;107
    const std::string FG256_108 = "\033[38;5;108m"; //38;5;108
    const std::string FG256_109 = "\033[38;5;109m"; //38;5;109
    const std::string FG256_110 = "\033[38;5;110m"; //38;5;110
    const std::string FG256_111 = "\033[38;5;111m"; //38;5;111
    const std::string FG256_112 = "\033[38;5;112m"; //38;5;112
    const std::string FG256_113 = "\033[38;5;113m"; //38;5;113
    const std::string FG256_114 = "\033[38;5;114m"; //38;5;114
    const std::string FG256_115 = "\033[38;5;115m"; //38;5;115
    const std::string FG256_116 = "\033[38;5;116m"; //38;5;116 
    const std::string FG256_117 = "\033[38;5;117m"; //38;5;117
    const std::string FG256_118 = "\033[38;5;118m"; //38;5;118
    const std::string FG256_119 = "\033[38;5;119m"; //38;5;119
    const std::string FG256_120 = "\033[38;5;120m"; //38;5;120
    const std::string FG256_121 = "\033[38;5;121m"; //38;5;121
    const std::string FG256_122 = "\033[38;5;122m"; //38;5;122
    const std::string FG256_123 = "\033[38;5;123m"; //38;5;123
    const std::string FG256_124 = "\033[38;5;124m"; //38;5;124
    const std::string FG256_125 = "\033[38;5;125m"; //38;5;125
    const std::string FG256_126 = "\033[38;5;126m"; //38;5;126
    const std::string FG256_127 = "\033[38;5;127m"; //38;5;127
    const std::string FG256_128 = "\033[38;5;128m"; //38;5;128
    const std::string FG256_129 = "\033[38;5;129m"; //38;5;129
    const std::string FG256_130 = "\033[38;5;130m"; //38;5;130
    const std::string FG256_131 = "\033[38;5;131m"; //38;5;131
    const std::string FG256_132 = "\033[38;5;132m"; //38;5;132
    const std::string FG256_133 = "\033[38;5;133m"; //38;5;133
    const std::string FG256_134 = "\033[38;5;134m"; //38;5;134
    const std::string FG256_135 = "\033[38;5;135m"; //38;5;135
    const std::string FG256_136 = "\033[38;5;136m"; //38;5;136
    const std::string FG256_137 = "\033[38;5;137m"; //38;5;137
    const std::string FG256_138 = "\033[38;5;138m"; //38;5;138
    const std::string FG256_139 = "\033[38;5;139m"; //38;5;139
    const std::string FG256_140 = "\033[38;5;140m"; //38;5;140
    const std::string FG256_141 = "\033[38;5;141m"; //38;5;141
    const std::string FG256_142 = "\033[38;5;142m"; //38;5;142
    const std::string FG256_143 = "\033[38;5;143m"; //38;5;143
    const std::string FG256_144 = "\033[38;5;144m"; //38;5;144
    const std::string FG256_145 = "\033[38;5;145m"; //38;5;145
    const std::string FG256_146 = "\033[38;5;146m"; //38;5;146
    const std::string FG256_147 = "\033[38;5;147m"; //38;5;147
    const std::string FG256_148 = "\033[38;5;148m"; //38;5;148
    const std::string FG256_149 = "\033[38;5;149m"; //38;5;149
    const std::string FG256_150 = "\033[38;5;150m"; //38;5;150
    const std::string FG256_151 = "\033[38;5;151m"; //38;5;151
    const std::string FG256_152 = "\033[38;5;152m"; //38;5;152
    const std::string FG256_153 = "\033[38;5;153m"; //38;5;153
    const std::string FG256_154 = "\033[38;5;154m"; //38;5;154
    const std::string FG256_155 = "\033[38;5;155m"; //38;5;155
    const std::string FG256_156 = "\033[38;5;156m"; //38;5;156
    const std::string FG256_157 = "\033[38;5;157m"; //38;5;157
    const std::string FG256_158 = "\033[38;5;158m"; //38;5;158 
    const std::string FG256_159 = "\033[38;5;159m"; //38;5;159
    const std::string FG256_160 = "\033[38;5;160m"; //38;5;160
    const std::string FG256_161 = "\033[38;5;161m"; //38;5;161
    const std::string FG256_162 = "\033[38;5;162m"; //38;5;162 
    const std::string FG256_163 = "\033[38;5;163m"; //38;5;163
    const std::string FG256_164 = "\033[38;5;164m"; //38;5;164
    const std::string FG256_165 = "\033[38;5;165m"; //38;5;165
    const std::string FG256_166 = "\033[38;5;166m"; //38;5;166
    const std::string FG256_167 = "\033[38;5;167m"; //38;5;167
    const std::string FG256_168 = "\033[38;5;168m"; //38;5;168
    const std::string FG256_169 = "\033[38;5;169m"; //38;5;169
    const std::string FG256_170 = "\033[38;5;170m"; //38;5;170
    const std::string FG256_171 = "\033[38;5;171m"; //38;5;171
    const std::string FG256_172 = "\033[38;5;172m"; //38;5;172
    const std::string FG256_173 = "\033[38;5;173m"; //38;5;173
    const std::string FG256_174 = "\033[38;5;174m"; //38;5;174
    const std::string FG256_175 = "\033[38;5;175m"; //38;5;175
    const std::string FG256_176 = "\033[38;5;176m"; //38;5;176
    const std::string FG256_177 = "\033[38;5;177m"; //38;5;177
    const std::string FG256_178 = "\033[38;5;178m"; //38;5;178
    const std::string FG256_179 = "\033[38;5;179m"; //38;5;179
    const std::string FG256_180 = "\033[38;5;180m"; //38;5;180
    const std::string FG256_181 = "\033[38;5;181m"; //38;5;181
    const std::string FG256_182 = "\033[38;5;182m"; //38;5;182
    const std::string FG256_183 = "\033[38;5;183m"; //38;5;183
    const std::string FG256_184 = "\033[38;5;184m"; //38;5;184
    const std::string FG256_185 = "\033[38;5;185m"; //38;5;185
    const std::string FG256_186 = "\033[38;5;186m"; //38;5;186
    const std::string FG256_187 = "\033[38;5;187m"; //38;5;187
    const std::string FG256_188 = "\033[38;5;188m"; //38;5;188
    const std::string FG256_189 = "\033[38;5;189m"; //38;5;189
    const std::string FG256_190 = "\033[38;5;190m"; //38;5;190
    const std::string FG256_191 = "\033[38;5;191m"; //38;5;191
    const std::string FG256_192 = "\033[38;5;192m"; //38;5;192
    const std::string FG256_193 = "\033[38;5;193m"; //38;5;193
    const std::string FG256_194 = "\033[38;5;194m"; //38;5;194
    const std::string FG256_195 = "\033[38;5;195m"; //38;5;195
    const std::string FG256_196 = "\033[38;5;196m"; //38;5;196
    const std::string FG256_197 = "\033[38;5;197m"; //38;5;197
    const std::string FG256_198 = "\033[38;5;198m"; //38;5;198
    const std::string FG256_199 = "\033[38;5;199m"; //38;5;199
    const std::string FG256_200 = "\033[38;5;200m"; //38;5;200
    const std::string FG256_201 = "\033[38;5;201m"; //38;5;201
    const std::string FG256_202 = "\033[38;5;202m"; //38;5;202
    const std::string FG256_203 = "\033[38;5;203m"; //38;5;203
    const std::string FG256_204 = "\033[38;5;204m"; //38;5;204
    const std::string FG256_205 = "\033[38;5;205m"; //38;5;205
    const std::string FG256_206 = "\033[38;5;206m"; //38;5;206
    const std::string FG256_207 = "\033[38;5;207m"; //38;5;207
    const std::string FG256_208 = "\033[38;5;208m"; //38;5;208
    const std::string FG256_209 = "\033[38;5;209m"; //38;5;209
    const std::string FG256_210 = "\033[38;5;210m"; //38;5;210
    const std::string FG256_211 = "\033[38;5;211m"; //38;5;211
    const std::string FG256_212 = "\033[38;5;212m"; //38;5;212
    const std::string FG256_213 = "\033[38;5;213m"; //38;5;213
    const std::string FG256_214 = "\033[38;5;214m"; //38;5;214 
    const std::string FG256_215 = "\033[38;5;215m"; //38;5;215
    const std::string FG256_216 = "\033[38;5;216m"; //38;5;216
    const std::string FG256_217 = "\033[38;5;217m"; //38;5;217
    const std::string FG256_218 = "\033[38;5;218m"; //38;5;218
    const std::string FG256_219 = "\033[38;5;219m"; //38;5;219
    const std::string FG256_220 = "\033[38;5;220m"; //38;5;220
    const std::string FG256_221 = "\033[38;5;221m"; //38;5;221 
    const std::string FG256_222 = "\033[38;5;222m"; //38;5;222
    const std::string FG256_223 = "\033[38;5;223m"; //38;5;223
    const std::string FG256_224 = "\033[38;5;224m"; //38;5;224
    const std::string FG256_225 = "\033[38;5;225m"; //38;5;225
    const std::string FG256_226 = "\033[38;5;226m"; //38;5;226
    const std::string FG256_227 = "\033[38;5;227m"; //38;5;227
    const std::string FG256_228 = "\033[38;5;228m"; //38;5;228
    const std::string FG256_229 = "\033[38;5;229m"; //38;5;229
    const std::string FG256_230 = "\033[38;5;230m"; //38;5;230
    const std::string FG256_231 = "\033[38;5;231m"; //38;5;231
    const std::string FG256_232 = "\033[38;5;232m"; //38;5;232
    const std::string FG256_233 = "\033[38;5;233m"; //38;5;233 
    const std::string FG256_234 = "\033[38;5;234m"; //38;5;234
    const std::string FG256_235 = "\033[38;5;235m"; //38;5;235
    const std::string FG256_236 = "\033[38;5;236m"; //38;5;236
    const std::string FG256_237 = "\033[38;5;237m"; //38;5;237
    const std::string FG256_238 = "\033[38;5;238m"; //38;5;238
    const std::string FG256_239 = "\033[38;5;239m"; //38;5;239
    const std::string FG256_240 = "\033[38;5;240m"; //38;5;240
    const std::string FG256_241 = "\033[38;5;241m"; //38;5;241
    const std::string FG256_242 = "\033[38;5;242m"; //38;5;242
    const std::string FG256_243 = "\033[38;5;243m"; //38;5;243 
    const std::string FG256_244 = "\033[38;5;244m"; //38;5;244
    const std::string FG256_245 = "\033[38;5;245m"; //38;5;245
    const std::string FG256_246 = "\033[38;5;246m"; //38;5;246
    const std::string FG256_247 = "\033[38;5;247m"; //38;5;247
    const std::string FG256_248 = "\033[38;5;248m"; //38;5;248
    const std::string FG256_249 = "\033[38;5;249m"; //38;5;249
    const std::string FG256_250 = "\033[38;5;250m"; //38;5;250
    const std::string FG256_251 = "\033[38;5;251m"; //38;5;251
    const std::string FG256_252 = "\033[38;5;252m"; //38;5;252 
    const std::string FG256_253 = "\033[38;5;253m"; //38;5;253
    const std::string FG256_254 = "\033[38;5;254m"; //38;5;254
    const std::string FG256_255 = "\033[38;5;255m"; //38;5;255
    const std::string FG256_256 = "\033[38;5;256m"; //38;5;256
  };

  //background colours - 256 colours
  struct BGColours256 {
  public:
    const std::string BG256_0 = "\033[48;5;0m"; //48;5;0
    const std::string BG256_1 = "\033[48;5;1m"; //48;5;1
    const std::string BG256_2 = "\033[48;5;2m"; //48;5;2
    const std::string BG256_3 = "\033[48;5;3m"; //48;5;3
    const std::string BG256_4 = "\033[48;5;4m"; //48;5;4
    const std::string BG256_5 = "\033[48;5;5m"; //48;5;5
    const std::string BG256_6 = "\033[48;5;6m"; //48;5;6
    const std::string BG256_7 = "\033[48;5;7m"; //48;5;7
    const std::string BG256_8 = "\033[48;5;8m"; //48;5;8
    const std::string BG256_9 = "\033[48;5;9m"; //48;5;9
    const std::string BG256_10 = "\033[48;5;10m"; //48;5;10
    const std::string BG256_11 = "\033[48;5;11m"; //48;5;11
    const std::string BG256_12 = "\033[48;5;12m"; //48;5;12
    const std::string BG256_13 = "\033[48;5;13m"; //48;5;13
    const std::string BG256_14 = "\033[48;5;14m"; //48;5;14
    const std::string BG256_15 = "\033[48;5;15m"; //48;5;15
    const std::string BG256_16 = "\033[48;5;16m"; //48;5;16
    const std::string BG256_17 = "\033[48;5;17m"; //48;5;17
    const std::string BG256_18 = "\033[48;5;18m"; //48;5;18
    const std::string BG256_19 = "\033[48;5;19m"; //48;5;19
    const std::string BG256_20 = "\033[48;5;20m"; //48;5;20
    const std::string BG256_21 = "\033[48;5;21m"; //48;5;21
    const std::string BG256_22 = "\033[48;5;22m"; //48;5;22
    const std::string BG256_23 = "\033[48;5;23m"; //48;5;23
    const std::string BG256_24 = "\033[48;5;24m"; //48;5;24
    const std::string BG256_25 = "\033[48;5;25m"; //48;5;25
    const std::string BG256_26 = "\033[48;5;26m"; //48;5;26
    const std::string BG256_27 = "\033[48;5;27m"; //48;5;27
    const std::string BG256_28 = "\033[48;5;28m"; //48;5;28 
    const std::string BG256_29 = "\033[48;5;29m"; //48;5;29 
    const std::string BG256_30 = "\033[48;5;30m"; //48;5;30
    const std::string BG256_31 = "\033[48;5;31m"; //48;5;31
    const std::string BG256_32 = "\033[48;5;32m"; //48;5;32 
    const std::string BG256_33 = "\033[48;5;33m"; //48;5;33
    const std::string BG256_34 = "\033[48;5;34m"; //48;5;34
    const std::string BG256_35 = "\033[48;5;35m"; //48;5;35
    const std::string BG256_36 = "\033[48;5;36m"; //48;5;36
    const std::string BG256_37 = "\033[48;5;37m"; //48;5;37
    const std::string BG256_38 = "\033[48;5;38m"; //48;5;38
    const std::string BG256_39 = "\033[48;5;39m"; //48;5;39
    const std::string BG256_40 = "\033[48;5;40m"; //48;5;40
    const std::string BG256_41 = "\033[48;5;41m"; //48;5;41
    const std::string BG256_42 = "\033[48;5;42m"; //48;5;42
    const std::string BG256_43 = "\033[48;5;43m"; //48;5;43 
    const std::string BG256_44 = "\033[48;5;44m"; //48;5;44
    const std::string BG256_45 = "\033[48;5;45m"; //48;5;45 
    const std::string BG256_46 = "\033[48;5;46m"; //48;5;46
    const std::string BG256_47 = "\033[48;5;47m"; //48;5;47
    const std::string BG256_48 = "\033[48;5;48m"; //48;5;48
    const std::string BG256_49 = "\033[48;5;49m"; //48;5;49
    const std::string BG256_50 = "\033[48;5;50m"; //48;5;50
    const std::string BG256_51 = "\033[48;5;51m"; //48;5;51
    const std::string BG256_52 = "\033[48;5;52m"; //48;5;52
    const std::string BG256_53 = "\033[48;5;53m"; //48;5;53
    const std::string BG256_54 = "\033[48;5;54m"; //48;5;54
    const std::string BG256_55 = "\033[48;5;55m"; //48;5;55
    const std::string BG256_56 = "\033[48;5;56m"; //48;5;56
    const std::string BG256_57 = "\033[48;5;57m"; //48;5;57
    const std::string BG256_58 = "\033[48;5;58m"; //48;5;58
    const std::string BG256_59 = "\033[48;5;59m"; //48;5;59
    const std::string BG256_60 = "\033[48;5;60m"; //48;5;60
    const std::string BG256_61 = "\033[48;5;61m"; //48;5;61
    const std::string BG256_62 = "\033[48;5;62m"; //48;5;62
    const std::string BG256_63 = "\033[48;5;63m"; //48;5;63
    const std::string BG256_64 = "\033[48;5;64m"; //48;5;64
    const std::string BG256_65 = "\033[48;5;65m"; //48;5;65
    const std::string BG256_66 = "\033[48;5;66m"; //48;5;66
    const std::string BG256_67 = "\033[48;5;67m"; //48;5;67
    const std::string BG256_68 = "\033[48;5;68m"; //48;5;68
    const std::string BG256_69 = "\033[48;5;69m"; //48;5;69
    const std::string BG256_70 = "\033[48;5;70m"; //48;5;70
    const std::string BG256_71 = "\033[48;5;71m"; //48;5;71
    const std::string BG256_72 = "\033[48;5;72m"; //48;5;72
    const std::string BG256_73 = "\033[48;5;73m"; //48;5;73
    const std::string BG256_74 = "\033[48;5;74m"; //48;5;74
    const std::string BG256_75 = "\033[48;5;75m"; //48;5;75
    const std::string BG256_76 = "\033[48;5;76m"; //48;5;76
    const std::string BG256_77 = "\033[48;5;77m"; //48;5;77
    const std::string BG256_78 = "\033[48;5;78m"; //48;5;78
    const std::string BG256_79 = "\033[48;5;79m"; //48;5;79
    const std::string BG256_80 = "\033[48;5;80m"; //48;5;80
    const std::string BG256_81 = "\033[48;5;81m"; //48;5;81
    const std::string BG256_82 = "\033[48;5;82m"; //48;5;82
    const std::string BG256_83 = "\033[48;5;83m"; //48;5;83
    const std::string BG256_84 = "\033[48;5;84m"; //48;5;84 
    const std::string BG256_85 = "\033[48;5;85m"; //48;5;85
    const std::string BG256_86 = "\033[48;5;86m"; //48;5;86
    const std::string BG256_87 = "\033[48;5;87m"; //48;5;87
    const std::string BG256_88 = "\033[48;5;88m"; //48;5;88
    const std::string BG256_89 = "\033[48;5;89m"; //48;5;89
    const std::string BG256_90 = "\033[48;5;90m"; //48;5;90
    const std::string BG256_91 = "\033[48;5;91m"; //48;5;91
    const std::string BG256_92 = "\033[48;5;92m"; //48;5;92
    const std::string BG256_93 = "\033[48;5;93m"; //48;5;93
    const std::string BG256_94 = "\033[48;5;94m"; //48;5;94
    const std::string BG256_95 = "\033[48;5;95m"; //48;5;95
    const std::string BG256_96 = "\033[48;5;96m"; //48;5;96
    const std::string BG256_97 = "\033[48;5;97m"; //48;5;97
    const std::string BG256_98 = "\033[48;5;98m"; //48;5;98
    const std::string BG256_99 = "\033[48;5;99m"; //48;5;99
    const std::string BG256_100 = "\033[48;5;100m"; //48;5;100
    const std::string BG256_101 = "\033[48;5;101m"; //48;5;101
    const std::string BG256_102 = "\033[48;5;102m"; //48;5;102
    const std::string BG256_103 = "\033[48;5;103m"; //48;5;103
    const std::string BG256_104 = "\033[48;5;104m"; //48;5;104
    const std::string BG256_105 = "\033[48;5;105m"; //48;5;105
    const std::string BG256_106 = "\033[48;5;106m"; //48;5;106
    const std::string BG256_107 = "\033[48;5;107m"; //48;5;107
    const std::string BG256_108 = "\033[48;5;108m"; //48;5;108
    const std::string BG256_109 = "\033[48;5;109m"; //48;5;109
    const std::string BG256_110 = "\033[48;5;110m"; //48;5;110
    const std::string BG256_111 = "\033[48;5;111m"; //48;5;111
    const std::string BG256_112 = "\033[48;5;112m"; //48;5;112
    const std::string BG256_113 = "\033[48;5;113m"; //48;5;113
    const std::string BG256_114 = "\033[48;5;114m"; //48;5;114
    const std::string BG256_115 = "\033[48;5;115m"; //48;5;115
    const std::string BG256_116 = "\033[48;5;116m"; //48;5;116
    const std::string BG256_117 = "\033[48;5;117m"; //48;5;117
    const std::string BG256_118 = "\033[48;5;118m"; //48;5;118
    const std::string BG256_119 = "\033[48;5;119m"; //48;5;119
    const std::string BG256_120 = "\033[48;5;120m"; //48;5;120
    const std::string BG256_121 = "\033[48;5;121m"; //48;5;121
    const std::string BG256_122 = "\033[48;5;122m"; //48;5;122
    const std::string BG256_123 = "\033[48;5;123m"; //48;5;123
    const std::string BG256_124 = "\033[48;5;124m"; //48;5;124
    const std::string BG256_125 = "\033[48;5;125m"; //48;5;125 
    const std::string BG256_126 = "\033[48;5;126m"; //48;5;126
    const std::string BG256_127 = "\033[48;5;127m"; //48;5;127
    const std::string BG256_128 = "\033[48;5;128m"; //48;5;128
    const std::string BG256_129 = "\033[48;5;129m"; //48;5;129
    const std::string BG256_130 = "\033[48;5;130m"; //48;5;130
    const std::string BG256_131 = "\033[48;5;131m"; //48;5;131
    const std::string BG256_132 = "\033[48;5;132m"; //48;5;132
    const std::string BG256_133 = "\033[48;5;133m"; //48;5;133
    const std::string BG256_134 = "\033[48;5;134m"; //48;5;134
    const std::string BG256_135 = "\033[48;5;135m"; //48;5;135
    const std::string BG256_136 = "\033[48;5;136m"; //48;5;136
    const std::string BG256_137 = "\033[48;5;137m"; //48;5;137
    const std::string BG256_138 = "\033[48;5;138m"; //48;5;138
    const std::string BG256_139 = "\033[48;5;139m"; //48;5;139
    const std::string BG256_140 = "\033[48;5;140m"; //48;5;140
    const std::string BG256_141 = "\033[48;5;141m"; //48;5;141
    const std::string BG256_142 = "\033[48;5;142m"; //48;5;142
    const std::string BG256_143 = "\033[48;5;143m"; //48;5;143
    const std::string BG256_144 = "\033[48;5;144m"; //48;5;144
    const std::string BG256_145 = "\033[48;5;145m"; //48;5;145
    const std::string BG256_146 = "\033[48;5;146m"; //48;5;146
    const std::string BG256_147 = "\033[48;5;147m"; //48;5;147
    const std::string BG256_148 = "\033[48;5;148m"; //48;5;148
    const std::string BG256_149 = "\033[48;5;149m"; //48;5;149
    const std::string BG256_150 = "\033[48;5;150m"; //48;5;150
    const std::string BG256_151 = "\033[48;5;151m"; //48;5;151
    const std::string BG256_152 = "\033[48;5;152m"; //48;5;152
    const std::string BG256_153 = "\033[48;5;153m"; //48;5;153
    const std::string BG256_154 = "\033[48;5;154m"; //48;5;154
    const std::string BG256_155 = "\033[48;5;155m"; //48;5;155
    const std::string BG256_156 = "\033[48;5;156m"; //48;5;156
    const std::string BG256_157 = "\033[48;5;157m"; //48;5;157
    const std::string BG256_158 = "\033[48;5;158m"; //48;5;158
    const std::string BG256_159 = "\033[48;5;159m"; //48;5;159
    const std::string BG256_160 = "\033[48;5;160m"; //48;5;160
    const std::string BG256_161 = "\033[48;5;161m"; //48;5;161
    const std::string BG256_162 = "\033[48;5;162m"; //48;5;162
    const std::string BG256_163 = "\033[48;5;163m"; //48;5;163 
    const std::string BG256_164 = "\033[48;5;164m"; //48;5;164
    const std::string BG256_165 = "\033[48;5;165m"; //48;5;165
    const std::string BG256_166 = "\033[48;5;166m"; //48;5;166
    const std::string BG256_167 = "\033[48;5;167m"; //48;5;167
    const std::string BG256_168 = "\033[48;5;168m"; //48;5;168
    const std::string BG256_169 = "\033[48;5;169m"; //48;5;169
    const std::string BG256_170 = "\033[48;5;170m"; //48;5;170
    const std::string BG256_171 = "\033[48;5;171m"; //48;5;171 
    const std::string BG256_172 = "\033[48;5;172m"; //48;5;172
    const std::string BG256_173 = "\033[48;5;173m"; //48;5;173
    const std::string BG256_174 = "\033[48;5;174m"; //48;5;174
    const std::string BG256_175 = "\033[48;5;175m"; //48;5;175
    const std::string BG256_176 = "\033[48;5;176m"; //48;5;176
    const std::string BG256_177 = "\033[48;5;177m"; //48;5;177
    const std::string BG256_178 = "\033[48;5;178m"; //48;5;178
    const std::string BG256_179 = "\033[48;5;179m"; //48;5;179
    const std::string BG256_180 = "\033[48;5;180m"; //48;5;180
    const std::string BG256_181 = "\033[48;5;181m"; //48;5;181
    const std::string BG256_182 = "\033[48;5;182m"; //48;5;182
    const std::string BG256_183 = "\033[48;5;183m"; //48;5;183
    const std::string BG256_184 = "\033[48;5;184m"; //48;5;184
    const std::string BG256_185 = "\033[48;5;185m"; //48;5;185
    const std::string BG256_186 = "\033[48;5;186m"; //48;5;186
    const std::string BG256_187 = "\033[48;5;187m"; //48;5;187
    const std::string BG256_188 = "\033[48;5;188m"; //48;5;188
    const std::string BG256_189 = "\033[48;5;189m"; //48;5;189
    const std::string BG256_190 = "\033[48;5;190m"; //48;5;190
    const std::string BG256_191 = "\033[48;5;191m"; //48;5;191
    const std::string BG256_192 = "\033[48;5;192m"; //48;5;192
    const std::string BG256_193 = "\033[48;5;193m"; //48;5;193
    const std::string BG256_194 = "\033[48;5;194m"; //48;5;194
    const std::string BG256_195 = "\033[48;5;195m"; //48;5;195
    const std::string BG256_196 = "\033[48;5;196m"; //48;5;196
    const std::string BG256_197 = "\033[48;5;197m"; //48;5;197
    const std::string BG256_198 = "\033[48;5;198m"; //48;5;198
    const std::string BG256_199 = "\033[48;5;199m"; //48;5;199
    const std::string BG256_200 = "\033[48;5;200m"; //48;5;200
    const std::string BG256_201 = "\033[48;5;201m"; //48;5;201
    const std::string BG256_202 = "\033[48;5;202m"; //48;5;202
    const std::string BG256_203 = "\033[48;5;203m"; //48;5;203
    const std::string BG256_204 = "\033[48;5;204m"; //48;5;204
    const std::string BG256_205 = "\033[48;5;205m"; //48;5;205
    const std::string BG256_206 = "\033[48;5;206m"; //48;5;206
    const std::string BG256_207 = "\033[48;5;207m"; //48;5;207
    const std::string BG256_208 = "\033[48;5;208m"; //47;5;208
    const std::string BG256_209 = "\033[48;5;209m"; //47;5;209
    const std::string BG256_210 = "\033[48;5;210m"; //47;5;210
    const std::string BG256_211 = "\033[48;5;211m"; //47;5;211
    const std::string BG256_212 = "\033[48;5;212m"; //48;5;212
    const std::string BG256_213 = "\033[48;5;213m"; //48;5;213
    const std::string BG256_214 = "\033[48;5;214m"; //48;5;214
    const std::string BG256_215 = "\033[48;5;215m"; //48;5;215
    const std::string BG256_216 = "\033[48;5;216m"; //48;5;216
    const std::string BG256_217 = "\033[48;5;217m"; //48;5;217
    const std::string BG256_218 = "\033[48;5;218m"; //48;5;218
    const std::string BG256_219 = "\033[48;5;219m"; //48;5;219
    const std::string BG256_220 = "\033[48;5;220m"; //48;5;220
    const std::string BG256_221 = "\033[48;5;221m"; //48;5;221
    const std::string BG256_222 = "\033[48;5;222m"; //48;5;222
    const std::string BG256_223 = "\033[48;5;223m"; //48;5;223
    const std::string BG256_224 = "\033[48;5;224m"; //48;5;224
    const std::string BG256_225 = "\033[48;5;225m"; //48;5;225
    const std::string BG256_226 = "\033[48;5;226m"; //48;5;226
    const std::string BG256_227 = "\033[48;5;227m"; //48;5;227
    const std::string BG256_228 = "\033[48;5;228m"; //48;5;228
    const std::string BG256_229 = "\033[48;5;229m"; //48;5;229
    const std::string BG256_230 = "\033[48;5;230m"; //48;5;230
    const std::string BG256_231 = "\033[48;5;231m"; //48;5;231
    const std::string BG256_232 = "\033[48;5;232m"; //48;5;232
    const std::string BG256_233 = "\033[48;5;233m"; //48;5;233
    const std::string BG256_234 = "\033[48;5;234m"; //48;5;234
    const std::string BG256_235 = "\033[48;5;235m"; //48;5;235
    const std::string BG256_236 = "\033[48;5;236m"; //48;5;236
    const std::string BG256_237 = "\033[48;5;237m"; //48;5;237
    const std::string BG256_238 = "\033[48;5;238m"; //48;5;238
    const std::string BG256_239 = "\033[48;5;239m"; //48;5;239
    const std::string BG256_240 = "\033[48;5;240m"; //48;5;240
    const std::string BG256_241 = "\033[48;5;241m"; //48;5;241
    const std::string BG256_242 = "\033[48;5;242m"; //48;5;242
    const std::string BG256_243 = "\033[48;5;243m"; //48;5;243
    const std::string BG256_244 = "\033[48;5;244m"; //48;5;244
    const std::string BG256_245 = "\033[48;5;245m"; //48;5;245
    const std::string BG256_246 = "\033[48;5;246m"; //48;5;246
    const std::string BG256_247 = "\033[48;5;247m"; //48;5;247
    const std::string BG256_248 = "\033[48;5;248m"; //48;5;248
    const std::string BG256_249 = "\033[48;5;249m"; //48;5;249
    const std::string BG256_250 = "\033[48;5;250m"; //48;5;250
    const std::string BG256_251 = "\033[48;5;251m"; //48;5;251
    const std::string BG256_252 = "\033[48;5;252m"; //48;5;252
    const std::string BG256_253 = "\033[48;5;253m"; //48;5;253
    const std::string BG256_254 = "\033[48;5;254m"; //48;5;254
    const std::string BG256_255 = "\033[48;5;255m"; //48;5;255
    const std::string BG256_256 = "\033[48;5;256m"; //48;5;256
  };  
  //this unnamed namespace holds created objects from structs.
  //it allows the users to directly access the member values
  //which contain the ansi escape codes.
  namespace {
    //object EO_ATTRS of Attributes struct
    Attributes EO_ATTRS;

    //object EO_RESET of Reset struct
    Reset EO_RESET;

    //object EO_FG816 of FGColours816 struct
    FGColours816 EO_FG816;

    //object EO_BG816 of BGColours816 struct
    BGColours816 EO_BG816;

    //object EO_FG256 of FGColours256 struct
    FGColours256 EO_FG256;

    //object EO_BG256 of BGColours256 struct
    BGColours256 EO_BG256;
  }
  namespace obj_internal {
    Attributes inline ATTRS;

    //object RESET of Reset struct
    Reset inline RESET;

    //object FG816 of FGColours816 struct
    FGColours816 inline FG816;

    //object BG816 of BGColours816 struct
    BGColours816 inline BG816;
    
    //object FG256 of FGColours256 struct
    FGColours256 inline FG256;

    //object BG256 of BGColours256 struct
    BGColours256 inline BG256;    
  }
    //0: reset default
  template<typename RESETDefault>
  std::basic_ostream<RESETDefault> & RESET_Default(std::basic_ostream<RESETDefault> &os) {
    os << obj_internal::RESET.RESET_Default;
    
    return os;
  }
}
#endif
