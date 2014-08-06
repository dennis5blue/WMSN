function channelGainToBS = CalChannelGainToBS (x,y)
% position of BS is at (0,0)
n0                          = 1e-19; %= pow(10,-17.4)/1000;Watt, ref:Steven ( Mouda: 1e-16 )
pathLoss0_MacroUE           = 131.1; % no unit ref:LTE release 9
pathLossAlpha_MacroUE       = 42.68; % no unit ref:LTE release 9
pathLoss0_MacroUE_Gib       = 131.1; % For simulation Adjustment
pathLossAlpha_MacroUE_Gib   = 42.68; 

tempDib = (0 - x)^2 + (0 - y)^2;
pathLossDBMacroUE = pathLoss0_MacroUE + pathLossAlpha_MacroUE * (0.5*log10(tempDib) - 3);
channelGainToBS = 10^( -(pathLossDBMacroUE/10) );
end