classdef ClockCounter < handle
   
    properties (Constant)
        
        NLINE = { ...
            [1 2 3 4 5 6],          ... % 0
            [2 3],                  ... % 1
            [1 2 7 5 4],            ... % 2
            [1 2 3 4 7],            ... % 3
            [6 7 2 3],              ... % 4
            [1 6 7 3 4],            ... % 5
            [1 6 5 4 3 7],          ... % 6
            [1 2 3],                ... % 7
            [1 2 3 4 5 6 7],        ... % 8
            [1 2 3 4 6 7]           ... % 9
            };
        
    end
    
    properties (Access = private)
        
        AxParent;
        
        NbMinDecade;
        NbMinUnits;
        
        NbSecDecade;
        NbSecUnits;
        
        PtSeparator;
        
        TxTeam;
                        
    end
    
    properties (Dependent, GetAccess = private, SetAccess = public)
        CurrentTime;
    end
    
    %% CONSTRUCTOR
    methods
        
        function [this] = ClockCounter(ax_hdl)
            
            this.AxParent = ax_hdl;
            
            set(ax_hdl, ...
                'XLim',         [0 8], ...
                'XLimMode',     'manual', ...
                'YLim',         [0 2], ...
                'YLimMode',     'manual')
            
            x = 0.5;            
            this.NbMinDecade = [ ...
                horizontal_bar(this.AxParent,   x+0,    2), ...
                vertical_bar(this.AxParent,     x+1,    1), ...
                vertical_bar(this.AxParent,     x+1,    0), ...
                horizontal_bar(this.AxParent,   x+0,    0), ...
                vertical_bar(this.AxParent,     x+0,    0), ...
                vertical_bar(this.AxParent,     x+0,    1), ...
                horizontal_bar(this.AxParent,   x+0,    1)];
            
            x = x + 1.5;
            this.NbMinUnits = [ ...
                horizontal_bar(this.AxParent,   x+0,    2), ...
                vertical_bar(this.AxParent,     x+1,    1), ...
                vertical_bar(this.AxParent,     x+1,    0), ...
                horizontal_bar(this.AxParent,   x+0,    0), ...
                vertical_bar(this.AxParent,     x+0,    0), ...
                vertical_bar(this.AxParent,     x+0,    1), ...
                horizontal_bar(this.AxParent,   x+0,    1)];
            
            x = x + 1.5;
            sep_size = [0.4 0.4];
            this.PtSeparator = [ ...
                patch(x + sep_size(1)/2 * [-1 1 1 -1], 0.5 + sep_size(2)/2 * [-1 -1 1 1], [0 0 0], 'Parent', ax_hdl), ...
                patch(x + sep_size(1)/2 * [-1 1 1 -1], 1.5 + sep_size(2)/2 * [-1 -1 1 1], [0 0 0], 'Parent', ax_hdl) ...
                ];
            set(this.PtSeparator, 'Visible', 'off')
            
            x = x + 0.5;
            this.NbSecDecade = [ ...
                horizontal_bar(this.AxParent,   x+0,    2), ...
                vertical_bar(this.AxParent,     x+1,    1), ...
                vertical_bar(this.AxParent,     x+1,    0), ...
                horizontal_bar(this.AxParent,   x+0,    0), ...
                vertical_bar(this.AxParent,     x+0,    0), ...
                vertical_bar(this.AxParent,     x+0,    1), ...
                horizontal_bar(this.AxParent,   x+0,    1)];
            
            x = x + 1.5;
            this.NbSecUnits = [ ...
                horizontal_bar(this.AxParent,   x+0,    2), ...
                vertical_bar(this.AxParent,     x+1,    1), ...
                vertical_bar(this.AxParent,     x+1,    0), ...
                horizontal_bar(this.AxParent,   x+0,    0), ...
                vertical_bar(this.AxParent,     x+0,    0), ...
                vertical_bar(this.AxParent,     x+0,    1), ...
                horizontal_bar(this.AxParent,   x+0,    1)];
                        
            
            x = x + 1.5;
            this.TxTeam(1) = text(x,1.5,'A', 'FontName', 'Arial Black', 'FontSize', 14);
            this.TxTeam(2) = text(x,1,  'B', 'FontName', 'Arial Black', 'FontSize', 14);
            this.TxTeam(3) = text(x,0.5,'C', 'FontName', 'Arial Black', 'FontSize', 14);
            set(this.TxTeam, 'Visible', 'off')
            
        end
        
    end
    
    methods
       
        function set.CurrentTime(this,value) % Value in seconds
            
            % Get number of minutes and seconds in input value
            nb_min = floor(value/60);
            
            % Manage case of more than 59 minutes (cannot display hours)
            if (nb_min < 60)
                nb_sec = floor(value - nb_min*60);
            else
                nb_min = 59;
                nb_sec = 59;
            end
            
            % Hide all numbers
            set(this.NbMinDecade,   'Visible', 'off')
            set(this.NbMinUnits,    'Visible', 'off')
            set(this.NbSecDecade,   'Visible', 'off')
            set(this.NbSecUnits,    'Visible', 'off')
            
            % Show lines to display correct numbers
            set(this.NbMinDecade(this.NLINE{floor(nb_min/10)+1}),                   'Visible', 'on')
            set(this.NbMinUnits(this.NLINE{floor(nb_min-10*floor(nb_min/10))+1}),   'Visible', 'on')
            set(this.NbSecDecade(this.NLINE{floor(nb_sec/10)+1}),                   'Visible', 'on')
            set(this.NbSecUnits(this.NLINE{floor(nb_sec-10*floor(nb_sec/10))+1}),   'Visible', 'on')
                    
            if strcmp(get(this.PtSeparator,'Visible'),'off')
                set(this.PtSeparator,'Visible','on')
            else
                set(this.PtSeparator,'Visible','off')
            end
            
        end
        
        function newTeam(this)
            
            idx = find(strcmp(get(this.TxTeam, 'Visible'),'on'),1);
            
            set(this.TxTeam(idx), 'Visible', 'off')
            
            if isempty(idx) || idx == length(this.TxTeam)
                idx = 1;
            else
                idx = idx + 1;
            end
            
            set(this.TxTeam(idx), 'Visible', 'on')
            
        end
        
        function setMode(this,mode)
           
            switch mode
                
                case {'warning'}
                    
                    color = [1 0 0];
                    
                otherwise
                    
                    color = [0 0 0];
                    
            end
            
            set([this.PtSeparator this.NbMinDecade this.NbMinUnits this.NbSecDecade this.NbSecUnits], 'FaceColor', color)
            set(this.TxTeam, 'Color', color)
            
        end
        
    end
    
end

function [bar_hdl] = vertical_bar(ax_hdl,x,y)
%% VERTICAL_BAR Création d'une barre verticale

% Création d'un patch pour représenter une barre verticale à la position x
% et y pour le point en bas à gauche
bar_hdl = patch(x + [-0.1 0 0.1 0.1 0 -0.1], ...
    y + [0.1 0 0.1 0.9 1 0.9], [0 0 0], ...
    'Parent', ax_hdl, 'Visible', 'off');

end

function [bar_hdl] = horizontal_bar(ax_hdl,x,y)
%% HORIZONTAL_BAR Création d'une barre horizontale

% Création d'un patch pour représenter une barre horizontale à la hauteur y
bar_hdl = patch(x+[0.05 0.1 0.9 0.95 0.9 0.1], ...
    y + [0 -0.1 -0.1 0 0.1 0.1], [0 0 0], ...
    'Parent', ax_hdl, 'Visible', 'off');

end
