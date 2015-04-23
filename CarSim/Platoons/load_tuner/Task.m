classdef Task
    %TASK Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        name;
        version;
        period;
        exectime;
        
        cost;
    end
    
    methods
        function self = Task(name, version, period, exectime, cost)
           self.name = name;
           self.version = version;
           self.period = period;
           self.exectime = exectime;
%            self.num_of_copies = num_of_copie;
           self.cost = cost;
        end
        

    end
    
end

