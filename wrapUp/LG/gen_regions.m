s_N_v = [11 11 12 12 13 13 14 14 15 15 15 16 16 16 17 17 17 18 18 18 19 19 19 20 20 20 20 21 21 21 21 22 22 22 22 22 23 23 23 23 23 24 24 24 24 24 24 25 25 25 25 25 25];
s_N_w = [7 8 8 9 8 9 9 10 9 10 11 10 11 12 11 12 13 11 12 13 12 13 14 12 13 14 15 13 14 15 16 13 14 15 16 17 14 15 16 17 18 14 15 16 17 18 19 15 16 17 18 19 20];

% s_N_v = s_N_v(5: 17);
% s_N_w = s_N_w(5: 17);

for i = 0.1 : 0.1 : 0.8
    s_N_v = [s_N_v s_N_v];
    s_N_w = [s_N_w s_N_w + 0.1];
end

s_FS_v = [11 12 13 13 14 14 15 16 17 18 18 19 19 20 20 21 21 22 23 24 25];
s_FS_w = [9 10 10 11 11 12 12 13 14 14 15 15 16 16 17 17 18 18 19 20 21];

% s_FS_v = s_FS_v(3: 9);
% s_FS_w = s_FS_w(3: 9);

% s_FS_v = s_FS_v(1: round(0.1 * size(s_FS_v, 2)));
% s_FS_w = s_FS_w(1: round(0.1 * size(s_FS_w, 2)));


for i = 0.1 : 0.1 : 0.9
    s_FS_v = [s_FS_v s_FS_v];
    s_FS_w = [s_FS_w s_FS_w + 0.1];
end

s_F_v = [];
s_F_w = [];

s_F_v = [11 12 13 14 15 16 17 17 18 19 19 20 21 21 22 23 23 24 25 25];
s_F_w = [7 7 7 8 8 9 9 10 10 10 11 11 11 12 12 12 13 13 13 14];

% s_F_v = s_F_v(1: round(0.1 * size(s_F_v, 2)));
% s_F_w = s_F_w(1: round(0.1 * size(s_F_w, 2)));


% for i = 11 : 25
%     index_N = find(s_N_v == i);
%     index_FS = find(s_FS_v == i);
%     N_w = s_N_w(index_N);
%     FS_w = s_FS_w(index_FS);
%     for j = 0 : i
%         if size(find(N_w == j), 2) == 0 && size(find(FS_w == j), 2) == 0
%             s_F_v = [s_F_v i];
%             s_F_w = [s_F_w j];
%         end
%     end
% end

for i = 0.1 : 0.1 : 0.9
    s_F_v = [s_F_v s_F_v];
    s_F_w = [s_F_w s_F_w + 0.1];
end


plot(s_N_v, s_N_w, 'gx', 'LineWidth', 4)
hold
plot(s_FS_v, s_FS_w, 'bx', 'LineWidth', 4);
plot(s_F_v, s_F_w, 'rx', 'LineWidth', 4)

         
X1 = [s_N_v' s_N_w'];
y1 = ones(size(s_N_v,2), 1);
X2 = [s_FS_v' s_FS_w'];
y2 = 2 * ones(size(s_FS_v, 2), 1);
X3 = [s_F_v(1:end)' s_F_w(1:end)'];
y3 = 3 * ones(size(s_F_v(1:end), 2), 1);

X = [X1;X2;X3];
y = [y1;y2;y3];

% 
% X = [X2;X3];
% y = [y2;y3];


X1_square = X(:, 1) .^2;
X2_sqaure = X(:, 2) .^ 2;
X1X2 = X(:, 1) .* X(:, 2);
X1_cube = X(:, 1) .^ 3;
X2_cube = X(:, 2) .^ 3;
X1X1X2 = X(:, 1) .* X1X2;
X1X2X2 = X1X2 .* X(:, 2);
%X = [X X1_square X2_sqaure X1X2 X1_cube X2_cube X1X1X2 X1X2X2];