classdef LogMessage < handle
% Copyright 2015 The MathWorks, Inc.   
    properties (Access = private)
        all_msg;
    end
    
    properties (Dependent, GetAccess = public, SetAccess = private)
        LastMessage;
    end
    
    methods
        
        function [msg] = get.LastMessage(obj)
            
            if ~isempty(obj.all_msg)
                msg = obj.all_msg{end};
            else
                msg = '';
            end
            
        end
        
    end
    
    methods (Access = protected)
        
        function addMessage(obj,varargin)
            
            if numel(varargin) == 1 % Only message is defined
            obj.all_msg = [obj.all_msg {'', varargin{1}}];
            elseif numel(varargin) == 2 % ID and message are defined
                obj.all_msg = [obj.all_msg {varargin{1}, varargin{2}}];
            end
            
        end
        
    end
    
end