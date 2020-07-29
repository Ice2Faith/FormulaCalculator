# FormulaCalculator
a calculator of base on string formula by double stack,using c++ implements
# introduce
https://blog.csdn.net/Ugex_Savelar/article/details/107581618
# running preview
please check ./realse/*.png
# using
公式计算器使用简介：    Ugex.Savelar
        常规双目运算符号：+ - * / % ^ ( )
                加、减、乘、除、取模、求幂
                用法：3+2*5-(2^3)%5
        拓展双目运算符号：sqrt log adds muls and or xor
                N次根、对数、累加、累乘、位与、位或、位异或
                用法：2 sqrt 4 + 1adds5+ 7 and 3
                说明：2sqrt4表示4开2次根，1adds5表示1+...+5
                        2log8表示求以2为底8的对数,7and3表示7位与3
        拓展单目运算符：
                ! neg per abs radian angle sin cos tan arcsin arccos arctan
                阶乘 负号 百分号 绝对值 转弧度 转角度 三角函数族
                用法：3!+5neg+50per+(60radian)sin
                说明：3!表示求3的阶乘，5neg表示负5,50per表示百分之50
                        60radian表示将60转换为弧度制，(60radian)sin表示求sin60角度
                [注意]:三角函数族计算需要使用弧度制，拥有运算符转换
        注意事项：
                运算符不区分大小写
                空格空白符号可以任意添加，只要不中断运算符
                空白符号指：ASCII字符：空格 回车 换行 制表符
                计算结果请检查isSuccess标志位，如果为false，计算失败，错误发生
                你可以使用getLastErrStr()获取错误描述
                使用getLastResult()获取计算结果，如果发生错误就是中间计算结果
                        如果未发生错误，就是正确结果
        综合使用案例：
                7 and 3 + 1 or 2 + 3 xor 0 + (0 not) and 3 +
                (60radian)sin + (30radian)cos + (30radian)tan + 3!+ 25per + 10neg + 180radian +
                2 sqrt 4 + 2 log 8 + 1 adds 5 + 1 muls 3 +
                ((3.14 * 2 - 6 / (2 % 10)) + (3 ^ 1)) / (4 / 2) +
                ((3 + 5 * (4 % (3 + 7)) / (2 ^ 2)) / 2 / 2) ^ 3 +
                3 * 2 * 2 / 4 + 5 * (2 - 4) + 6 / 3 + 12 % 10 + 2 ^ 3
                计算结果为：55.840994
