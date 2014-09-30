function fig = met2char()
% This is the machine-generated representation of a Handle Graphics object
% and its children.  Note that handle values may change when these objects
% are re-created. This may cause problems with any callbacks written to
% depend on the value of the handle at the time the object was saved.
%
% To reopen this object, just type the name of the M-file at the MATLAB
% prompt. The M-file and its associated MAT-file must be on your path.

load met2char

h0 = figure('Units','points', ...
	'Color',[0.752941176470588 0.752941176470588 0.752941176470588], ...
	'Colormap',mat0, ...
	'MenuBar','none', ...
	'Name','Two-Characteristics Method', ...
	'NumberTitle','off', ...
	'PointerShapeCData',mat1, ...
	'Position',[98.25 29.25 444 401.25], ...
	'Resize','off', ...
	'Tag','OknoM2Ch');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[0.752941176470588 0.752941176470588 0.752941176470588], ...
	'FontAngle','oblique', ...
	'FontName','Arial', ...
	'FontSize',24, ...
	'ForegroundColor',[1 0 0], ...
	'ListboxTop',0, ...
	'Position',[3 362.25 438.75 30], ...
	'String','Two-Characteristics Method', ...
	'Style','text', ...
	'Tag','HlavnyTitulok');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[0.752941176470588 0.752941176470588 0.752941176470588], ...
	'FontAngle','italic', ...
	'FontSize',12, ...
	'ListboxTop',0, ...
	'Position',[2.25 347.25 440.25 16.5], ...
	'String',mat2, ...
	'Style','text', ...
	'Tag','Podnadpis');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[0.752941176470588 0.752941176470588 0.752941176470588], ...
	'ListboxTop',0, ...
	'Position',[161.25 261 258.75 72.75], ...
	'Style','frame', ...
	'Tag','Ram1');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[0.752941176470588 0.752941176470588 0.752941176470588], ...
	'ListboxTop',0, ...
	'Position',[170.25 327.75 156 12], ...
	'String','Parameters of the linear part of the system', ...
	'Style','text', ...
	'Tag','LinearText');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[1 1 1], ...
	'Callback',mat3, ...
	'ListboxTop',0, ...
	'Position',[279.75 304.5 127.5 15], ...
	'Style','edit', ...
	'Tag','EditCitatel');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[1 1 1], ...
	'Callback',mat4, ...
	'ListboxTop',0, ...
	'Position',[280.5 285 127.5 15], ...
	'Style','edit', ...
	'Tag','EditMenovatel');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[0.752941176470588 0.752941176470588 0.752941176470588], ...
	'ListboxTop',0, ...
	'Position',[169.5 285.75 97.5 12.75], ...
	'String','Denominator coefficients:', ...
	'Style','text', ...
	'Tag','MenovText');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[0.752941176470588 0.752941176470588 0.752941176470588], ...
	'ListboxTop',0, ...
	'Position',[168 304.5 93 12.75], ...
	'String','Numerator coefficients:', ...
	'Style','text', ...
	'Tag','CitText');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[0.752941176470588 0.752941176470588 0.752941176470588], ...
	'ListboxTop',0, ...
	'Position',[166.5 264.75 106.5 15], ...
	'String','Frequency range (omega):', ...
	'Style','text', ...
	'Tag','TextRozsah');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[1 1 1], ...
	'Callback',mat5, ...
	'ListboxTop',0, ...
	'Position',[299.25 265.5 22.5 15], ...
	'Style','edit', ...
	'Tag','EditOd');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[1 1 1], ...
	'Callback',mat6, ...
	'ListboxTop',0, ...
	'Position',[339 265.5 22.5 15], ...
	'Style','edit', ...
	'Tag','EditDo');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[1 1 1], ...
	'Callback',mat7, ...
	'ListboxTop',0, ...
	'Position',[385.5 265.5 22.5 15], ...
	'Style','edit', ...
	'Tag','EditKrok');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[0.752941176470588 0.752941176470588 0.752941176470588], ...
	'ListboxTop',0, ...
	'Position',[278.25 266.25 18 12], ...
	'String','from:', ...
	'Style','text', ...
	'Tag','TextOd');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[0.752941176470588 0.752941176470588 0.752941176470588], ...
	'ListboxTop',0, ...
	'Position',[324 268.5 13.5 10.5], ...
	'String','to:', ...
	'Style','text', ...
	'Tag','TextDo');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[0.752941176470588 0.752941176470588 0.752941176470588], ...
	'ListboxTop',0, ...
	'Position',[363 267.75 21 11.25], ...
	'String','step:', ...
	'Style','text', ...
	'Tag','TextKrok');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[0.752941176470588 0.752941176470588 0.752941176470588], ...
	'ListboxTop',0, ...
	'Position',[161.25 174 260.25 72.75], ...
	'Style','frame', ...
	'Tag','Ram2');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[0.752941176470588 0.752941176470588 0.752941176470588], ...
	'ListboxTop',0, ...
	'Position',[173.25 240.75 141 11.25], ...
	'String','Describing function of the nonlinearity', ...
	'Style','text', ...
	'Tag','NelinearText');
h1 = axes('Parent',h0, ...
	'Units','pixels', ...
	'Box','on', ...
	'CameraUpVector',[0 1 0], ...
	'CameraUpVectorMode','manual', ...
	'Color',[1 1 1], ...
	'ColorOrder',mat8, ...
	'Layer','top', ...
	'Position',[17 244 188 74], ...
	'Tag','NelinObr', ...
	'Visible','off', ...
	'XColor',[0 0 0], ...
	'XLim',[0.5 297.5], ...
	'XLimMode','manual', ...
	'YColor',[0 0 0], ...
	'YDir','reverse', ...
	'YLim',[0.5 327.5], ...
	'YLimMode','manual', ...
	'ZColor',[0 0 0]);
h2 = image('Parent',h1, ...
	'CData',mat9, ...
	'Tag','Image2', ...
	'XData',[1 297], ...
	'YData',[1 327]);
h2 = text('Parent',h1, ...
	'Color',[0 0 0], ...
	'HandleVisibility','off', ...
	'HorizontalAlignment','center', ...
	'Position',[148.2058823529412 435.0068493150686 9.160254037844386], ...
	'Tag','Text8', ...
	'VerticalAlignment','cap', ...
	'Visible','off');
set(get(h2,'Parent'),'XLabel',h2);
h2 = text('Parent',h1, ...
	'Color',[0 0 0], ...
	'HandleVisibility','off', ...
	'HorizontalAlignment','center', ...
	'Position',[-50.3235294117647 170.7191780821918 9.160254037844386], ...
	'Rotation',90, ...
	'Tag','Text7', ...
	'VerticalAlignment','baseline', ...
	'Visible','off');
set(get(h2,'Parent'),'YLabel',h2);
h2 = text('Parent',h1, ...
	'Color',[0 0 0], ...
	'HandleVisibility','off', ...
	'HorizontalAlignment','right', ...
	'Position',[-26.5 -971.5410958904108 9.160254037844386], ...
	'Tag','Text6', ...
	'Visible','off');
set(get(h2,'Parent'),'ZLabel',h2);
h2 = text('Parent',h1, ...
	'Color',[0 0 0], ...
	'HandleVisibility','off', ...
	'HorizontalAlignment','center', ...
	'Position',[148.2058823529412 -30.85616438356158 9.160254037844386], ...
	'Tag','Text5', ...
	'VerticalAlignment','bottom', ...
	'Visible','off');
set(get(h2,'Parent'),'Title',h2);
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[1 1 1], ...
	'Callback',mat10, ...
	'ListboxTop',0, ...
	'Position',[282 216.75 127.5 15], ...
	'String',[' Ideal relay          ';' Relay with dead-zone ';' Relay with hysteresis';' Saturation           '], ...
	'Style','popupmenu', ...
	'Tag','MenuDruhNel', ...
	'Value',1);
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[0.752941176470588 0.752941176470588 0.752941176470588], ...
	'ListboxTop',0, ...
	'Position',[175.5 217.5 63.75 12.75], ...
	'String','Nonlinearity type:', ...
	'Style','text', ...
	'Tag','TextDruhNel');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[0.752941176470588 0.752941176470588 0.752941176470588], ...
	'ListboxTop',0, ...
	'Position',[176.25 198 84.75 13.5], ...
	'String','Nonlinearity parameters:', ...
	'Style','text', ...
	'Tag','TextParamNelin');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[1 1 1], ...
	'Callback',mat11, ...
	'ListboxTop',0, ...
	'Position',[303 198 37.5 15], ...
	'Style','edit', ...
	'Tag','EditK');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[1 1 1], ...
	'Callback',mat12, ...
	'ListboxTop',0, ...
	'Position',[368.25 198 41.25 15], ...
	'Style','edit', ...
	'Tag','EditB');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[0.752941176470588 0.752941176470588 0.752941176470588], ...
	'ListboxTop',0, ...
	'Position',[281.25 198 21.75 12.75], ...
	'String','K = ', ...
	'Style','text', ...
	'Tag','TextK');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[0.752941176470588 0.752941176470588 0.752941176470588], ...
	'ListboxTop',0, ...
	'Position',[345.75 196.5 21.75 14.25], ...
	'String','B = ', ...
	'Style','text', ...
	'Tag','TextB');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[0.752941176470588 0.752941176470588 0.752941176470588], ...
	'ListboxTop',0, ...
	'Position',[167.25 182.25 78.75 12], ...
	'String','Amplitude range:', ...
	'Style','text', ...
	'Tag','TextRozsahA');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[1 1 1], ...
	'Callback',mat13, ...
	'ListboxTop',0, ...
	'Position',[387 179.25 22.5 15], ...
	'Style','edit', ...
	'Tag','EditAKrok');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[1 1 1], ...
	'Callback',mat14, ...
	'ListboxTop',0, ...
	'Position',[339 179.25 22.5 15], ...
	'Style','edit', ...
	'Tag','EditADo');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[1 1 1], ...
	'Callback',mat15, ...
	'ListboxTop',0, ...
	'Position',[300 179.25 22.5 15], ...
	'Style','edit', ...
	'Tag','EditAOd');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[0.752941176470588 0.752941176470588 0.752941176470588], ...
	'ListboxTop',0, ...
	'Position',[277.5 182.25 20.25 9.75], ...
	'String','from:', ...
	'Style','text', ...
	'Tag','TextAOd');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[0.752941176470588 0.752941176470588 0.752941176470588], ...
	'ListboxTop',0, ...
	'Position',[324.75 181.5 13.5 10.5], ...
	'String','to:', ...
	'Style','text', ...
	'Tag','TextADo');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[0.752941176470588 0.752941176470588 0.752941176470588], ...
	'ListboxTop',0, ...
	'Position',[364.5 181.5 21 11.25], ...
	'String','step:', ...
	'Style','text', ...
	'Tag','TextAKrok');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[0.752941176470588 0.752941176470588 0.752941176470588], ...
	'ListboxTop',0, ...
	'Position',[17.25 45.75 123 114], ...
	'Style','frame', ...
	'Tag','RamGraf');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[0.752941176470588 0.752941176470588 0.752941176470588], ...
	'ListboxTop',0, ...
	'Position',[24.75 152.25 78.75 13.5], ...
	'String','Display range (axes):', ...
	'Style','text', ...
	'Tag','TextAxes');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'Callback',mat16, ...
	'Enable','off', ...
	'ListboxTop',0, ...
	'Position',[10.5 18 42 18], ...
	'String','Evaluate', ...
	'Tag','Pushbutton1');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'Callback','close(gcf);', ...
	'ListboxTop',0, ...
	'Position',[57 18 42 18], ...
	'String','Exit', ...
	'Tag','Pushbutton2');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'Callback','web(fullfile(cd,''help'',''met2char.html''));', ...
	'ListboxTop',0, ...
	'Position',[103.5 18 42 18], ...
	'String','Help', ...
	'Tag','Pushbutton3');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[0.752941176470588 0.752941176470588 0.752941176470588], ...
	'ListboxTop',0, ...
	'Position',[27.75 134.25 60 13.5], ...
	'String','Re - minimum:', ...
	'Style','text', ...
	'Tag','TextRoz1');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[0.752941176470588 0.752941176470588 0.752941176470588], ...
	'ListboxTop',0, ...
	'Position',[29.25 115.5 60 13.5], ...
	'String','Re - maximum:', ...
	'Style','text', ...
	'Tag','TextRoz2');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[0.752941176470588 0.752941176470588 0.752941176470588], ...
	'ListboxTop',0, ...
	'Position',[27.75 97.5 60 13.5], ...
	'String','Im - minimum:', ...
	'Style','text', ...
	'Tag','TextRoz3');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[0.752941176470588 0.752941176470588 0.752941176470588], ...
	'ListboxTop',0, ...
	'Position',[28.5 78 60 13.5], ...
	'String','Im - maximum:', ...
	'Style','text', ...
	'Tag','TextRoz4');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[1 1 1], ...
	'Callback',mat17, ...
	'ListboxTop',0, ...
	'Position',[96 134.25 31.5 15], ...
	'String','-15', ...
	'Style','edit', ...
	'Tag','EditRoz1');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[1 1 1], ...
	'Callback',mat18, ...
	'ListboxTop',0, ...
	'Position',[95.25 116.25 31.5 15], ...
	'String','0', ...
	'Style','edit', ...
	'Tag','EditRoz2');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[1 1 1], ...
	'Callback',mat19, ...
	'ListboxTop',0, ...
	'Position',[95.25 98.25 31.5 15], ...
	'String','-1', ...
	'Style','edit', ...
	'Tag','EditRoz3');
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[1 1 1], ...
	'Callback',mat20, ...
	'ListboxTop',0, ...
	'Position',[95.25 80.25 31.5 15], ...
	'String','1', ...
	'Style','edit', ...
	'Tag','EditRoz4');
h1 = axes('Parent',h0, ...
	'Units','pixels', ...
	'Box','on', ...
	'CameraUpVector',[0 1 0], ...
	'CameraUpVectorMode','manual', ...
	'Color',[1 1 1], ...
	'ColorOrder',mat21, ...
	'Layer','top', ...
	'Position',[16 374 188 50], ...
	'Tag','LinObr', ...
	'Visible','off', ...
	'XColor',[0 0 0], ...
	'XLim',[0.5 173.5], ...
	'XLimMode','manual', ...
	'YColor',[0 0 0], ...
	'YDir','reverse', ...
	'YLim',[0.5 47.5], ...
	'YLimMode','manual', ...
	'ZColor',[0 0 0]);
h2 = image('Parent',h1, ...
	'CData',mat22, ...
	'Tag','Image1', ...
	'XData',[1 173], ...
	'YData',[1 47]);
h2 = text('Parent',h1, ...
	'Color',[0 0 0], ...
	'HandleVisibility','off', ...
	'HorizontalAlignment','center', ...
	'Position',[86.53743315508022 70.5204081632653 9.160254037844386], ...
	'Tag','Text4', ...
	'VerticalAlignment','cap', ...
	'Visible','off');
set(get(h2,'Parent'),'XLabel',h2);
h2 = text('Parent',h1, ...
	'Color',[0 0 0], ...
	'HandleVisibility','off', ...
	'HorizontalAlignment','center', ...
	'Position',[-22.62834224598931 25.4387755102041 9.160254037844386], ...
	'Rotation',90, ...
	'Tag','Text3', ...
	'VerticalAlignment','baseline', ...
	'Visible','off');
set(get(h2,'Parent'),'YLabel',h2);
h2 = text('Parent',h1, ...
	'Color',[0 0 0], ...
	'HandleVisibility','off', ...
	'HorizontalAlignment','right', ...
	'Position',[-14.30213903743316 -105.969387755102 9.160254037844386], ...
	'Tag','Text2', ...
	'Visible','off');
set(get(h2,'Parent'),'ZLabel',h2);
h2 = text('Parent',h1, ...
	'Color',[0 0 0], ...
	'HandleVisibility','off', ...
	'HorizontalAlignment','center', ...
	'Position',[86.53743315508022 -6.214285714285708 9.160254037844386], ...
	'Tag','Text1', ...
	'VerticalAlignment','bottom', ...
	'Visible','off');
set(get(h2,'Parent'),'Title',h2);
h1 = uicontrol('Parent',h0, ...
	'Units','points', ...
	'BackgroundColor',[0.752941176470588 0.752941176470588 0.752941176470588], ...
	'Callback','if get(findall(gcf,''Tag'',''Mriezka''),''Value''),grid on;else,grid off;end', ...
	'ListboxTop',0, ...
	'Position',[39.75 54.75 87.75 15], ...
	'String','Display grid', ...
	'Style','checkbox', ...
	'Tag','Mriezka', ...
	'Value',1);
h1 = axes('Parent',h0, ...
	'Box','on', ...
	'CameraUpVector',[0 1 0], ...
	'CameraUpVectorMode','manual', ...
	'Color',[1 1 1], ...
	'ColorOrder',mat23, ...
	'NextPlot','add', ...
	'Position',[0.3918918918918919 0.04299065420560748 0.5574324324324325 0.3626168224299066], ...
	'Tag','Graf', ...
	'XColor',[0 0 0], ...
	'XGrid','on', ...
	'XLim',[-15 0], ...
	'XLimMode','manual', ...
	'YColor',[0 0 0], ...
	'YGrid','on', ...
	'YLim',[-1 1], ...
	'YLimMode','manual', ...
	'ZColor',[0 0 0], ...
	'ZGrid','on');
h2 = line('Parent',h1, ...
	'Color',[0 0 1], ...
	'Tag','GrafPlot1', ...
	'XData',[], ...
	'YData',[]);
h2 = line('Parent',h1, ...
	'Color',[1 0 0], ...
	'Tag','GrafPlot2', ...
	'XData',[], ...
	'YData',[]);
h2 = text('Parent',h1, ...
	'Color',[0 0 0], ...
	'HandleVisibility','off', ...
	'HorizontalAlignment','center', ...
	'Position',[-7.522796352583587 -1.248704663212435 9.160254037844386], ...
	'Tag','GrafXLabel', ...
	'VerticalAlignment','cap');
set(get(h2,'Parent'),'XLabel',h2);
h2 = text('Parent',h1, ...
	'Color',[0 0 0], ...
	'HandleVisibility','off', ...
	'HorizontalAlignment','center', ...
	'Position',mat24, ...
	'Rotation',90, ...
	'Tag','GrafYLabel', ...
	'VerticalAlignment','baseline');
set(get(h2,'Parent'),'YLabel',h2);
h2 = text('Parent',h1, ...
	'Color',[0 0 0], ...
	'HandleVisibility','off', ...
	'HorizontalAlignment','right', ...
	'Position',[-25.62310030395137 4.284974093264249 9.160254037844386], ...
	'Tag','GrafZLabel', ...
	'Visible','off');
set(get(h2,'Parent'),'ZLabel',h2);
h2 = text('Parent',h1, ...
	'Color',[0 0 0], ...
	'HandleVisibility','off', ...
	'HorizontalAlignment','center', ...
	'Position',[-7.522796352583587 1.072538860103627 9.160254037844386], ...
	'Tag','GrafNazov', ...
	'VerticalAlignment','bottom');
set(get(h2,'Parent'),'Title',h2);
h2 = image('Parent',h1, ...
	'CData',mat25, ...
	'Tag','GrafImage1', ...
	'XData',[1 189], ...
	'YData',[1 76]);
h2 = image('Parent',h1, ...
	'CData',mat26, ...
	'Tag','GrafImage2', ...
	'XData',[1 189], ...
	'YData',[1 76]);
if nargout > 0, fig = h0; end