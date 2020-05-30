#ifndef TEXT_H
#define TEXT_H

#include <iostream>

#define CLEAR system("printf \"\033c\"")
//#define CLEAR system("clear")
//#define CLEAR system("cls")
#define T(code, text) const std::string(code) = (text)

#define SAFE_DELETE(p)  \
    {                   \
        if (p)          \
        {               \
            delete (p); \
            (p) = NULL; \
        }               \
    }
#define DELETE_VECTOR(pL)   \
    {                       \
        for (auto it : pL)  \
        {                   \
            SAFE_DELETE(it) \
        }                   \
        pL.clear();         \
    }

namespace NCategory
{
    T(ROUTINE, "日常");
    T(FOOD, "饮食");
    T(CLOTHING, "服装");
    T(EDUCATION, "教育");
    T(ENTERTAINMENT, "娱乐");
    T(INTERNET, "网络");
    T(MISCELLANEOUS, "杂项");
    T(ADD_NEW_CATEGORY, "新建类别");

} // namespace NCategory

namespace NPeriod
{
    T(STR_MONTHLY, "按月");
    T(STR_WEEKLY, "按周");
    T(STR_DAILY, "按日");
    T(STR_NO_PERIOD, "-");
    T(END, "////////// ＝＝＝＝ //////////");

} // namespace NPeriod

namespace NDate
{
    T(YEAR, "年");
    T(MONTH, "月");
    T(DAY, "日");

} // namespace NDate

namespace NBill
{
    T(TYPE, "种类");
    T(AMOUNT, "金额");
    T(DATE, "日期");
    T(INFO, "附加信息");

    T(YUAN, "元");
    T(INCOME, "收入");
    T(EXPENSE, "支出");
    T(INTEREST, "利息");
    T(REGULAR, "定期");

    T(EXPECTED, "本月预计消费");
    T(USED, "已用");

} // namespace NBill

namespace NAssetMenu
{
    T(TITLE, "////////// 财产菜单 //////////");
    T(TRANSACTION, "收入和支出");
    T(DEPO_AND_LOAN, "借款和贷款");
    T(BUDGET, "预算");
    T(BACK, "返回");
    T(END, "////////// ＝＝＝＝ //////////");

} // namespace NAssetMenu

namespace NTransactionMenu
{
    T(TITLE, "////////// 收支菜单 //////////");
    T(ADD_SINGLE_EXPENSE, "添加单笔支出");
    T(ADD_SINGLE_INCOME, "添加单笔收入");
    T(ADD_REGULAR_EXPENSE, "添加定期支出");
    T(ADD_REGULAR_INCOME, "添加定期收入");
    T(EDIT, "编辑收支");
    T(DELETE, "删除收支");
    T(BACK, "返回");
    T(END, "////////// ＝＝＝＝ //////////");

} // namespace NTransactionMenu

namespace NBudgetMenu
{
    T(TITLE, "////////// 预算菜单 //////////");
    T(ADD, "添加预算");
    T(EDIT, "编辑预算");
    T(STATISTICS, "统计");
    T(BACK, "返回");
    T(END, "////////// ＝＝＝＝ //////////");

} // namespace NBudgetMenu

namespace NMainMenu
{
    T(TITLE, "/////////// 主菜单 ///////////");
    T(ASSET, "财产");
    T(BILL, "账单");
    T(WALLET, "钱包");
    T(MFILE, "文件");
    T(HELP, "帮助");
    T(REFRESH, "刷新");
    T(EXIT, "退出");
    T(END, "/////////// ＝＝＝ ///////////");
} // namespace NMainMenu

namespace NTransaction
{
    T(SINGLE_EXPENSE_TITLE, "////////// 单笔支出 //////////");
    T(SINGLE_INCOME_TITLE, "////////// 单笔收入 //////////");
    T(REGULAR_EXPENSE_TITLE, "////////// 定期支出 //////////");
    T(REGULAR_INCOME_TITLE, "////////// 定期收入 //////////");
    T(CHOOSE_A_TRANSACTION, "根据编号选择一个交易");
    T(PRESS_ENTER_TO_EXIT, "按下回车或输入 0 返回");
    T(AMOUNT, "金额");
    T(CATEGORY, "类别");
    T(DATE, "日期");
    T(START_DATE, "起始日期");
    T(TODAY_AS_DEFAULT, "默认今天");
    T(PERIOD, "周期");
    T(INFO, "附加信息");
    T(OPTIONAL, "可选");
    T(DIVISION, "-----------------------------");
    T(END, "////////// ＝＝＝＝ //////////");
    T(INCOME, "收入");
    T(EXPENSE, "支出");
    T(TYPE, "种类");
    T(EDIT, "编辑");
    T(DELETE, "删除");
    T(BACK, "返回");
    T(ID, "编号");

} // namespace NTransaction

namespace NInstruction
{

    T(COMFIRM_AND_SAVE, "确认并保存");
    T(INPUT_AGAIN, "重新输入");
    T(HELP, "帮助");
    T(BACK, "返回");
    T(END, "////////// ＝＝＝＝ //////////");

} // namespace NInstruction

namespace NError
{
    T(ERR_ILLEGAL_OPERATION, "不合法的运算");
    T(ERR_ILLEGAL_CATEGORY, "不合法的类别");
    T(ERR_ILLEGAL_NUMBER, "不合法的数字");
    T(ERR_NEGATIVE_NUMBER, "输入不能为负数");
    T(ERR_ILLEGAL_DATE, "不合法的日期");
    T(PLEASE_INPUT_AGAIN, "请重新输入");

} // namespace NError

namespace NDepositAndLoanMenu
{
    T(TITLE, "////////// 存贷菜单 //////////");
    T(ADD_DEPOSIT, "添加存款");
    T(ADD_LOAN, "添加贷款");
    T(EDIT, "编辑存贷");
    T(STATISTICS, "统计");
    T(BACK, "返回");
    T(END, "////////// ＝＝＝＝ //////////");

} // namespace NDepositAndLoanMenu

namespace NDepositAndLoan
{
    T(YUAN, "元");
    T(TOTAL_INCOME, "来自利息的总收入");
    T(TOTAL_EXPENSE, "来自利息的总支出");
    T(CHOOSE_A_DEPOSIT_OR_LOAN, "根据编号选择一个借贷");
    T(PRESS_ENTER_TO_EXIT, "按下回车或输入 0 返回");
    T(DEPOSIT, "存款");
    T(LOAN, "贷款");
    T(TYPE, "种类");
    T(ID, "编号");
    T(TITLE, "////////// 存款贷款 //////////");
    T(PRINCIPLE, "本金");
    T(INTEREST_RATE, "利率");
    T(INTEREST_TYPE, "利率类型");
    T(SIMPLE_INTEREST, "单利");
    T(COMPOUND_INTEREST, "复利");
    T(START_DATE, "起始日期");
    T(END_DATE, "结束日期");
    T(PERIOD, "周期");
    T(INFO, "附加信息");
    T(TOTAL_INTEREST, "总计利息");
    T(DIVISION, "-----------------------------");
    T(RATE_HELP, "利率前标记'S'的是单利, 标记'C'的是复利. ");
    T(DELETE, "删除");
    T(EDIT, "编辑");
    T(BACK, "返回");

} // namespace NDepositAndLoan

namespace NFilter
{
    T(TITLE, "/////////// 过滤器 ///////////");
    T(FILTER_BY_DATE, "按日期过滤");
    T(FILTER_BY_AMOUNT, "按金额过滤");
    T(FILTER_BY_TYPE, "按类别过滤");
    T(BACK, "返回");
    T(END, "/////////// ＝＝＝ ///////////");
    T(LOWER_LIMIT, "下限");
    T(UPPER_LIMIT, "上限");
} // namespace NFilter

namespace NBudget
{
    T(TITLE, "////////// 编辑预算 //////////");
    T(BUDGET, "预算");
    T(CATEGORY, "类别");
    T(START_DATE, "起始日期");
    T(DIVISION, "-----------------------------");

} // namespace NBudget

namespace NBillMenu
{
    T(TITLE, "////////// 账单菜单 //////////");
    T(OVERVIEW, "总览");
    T(FILTER, "过滤器");
    T(STATISTICS, "统计");
    T(BACK, "返回");
    T(END, "////////// ＝＝＝＝ //////////");

    T(OVERVIEW_TITLE, "//////////// 总览 ////////////");
    T(OVERVIEW_END, "//////////// ＝＝ ////////////");
    T(BY_DATE, "按日期");
    T(BY_AMOUNT, "按金额");
    T(ASCEND, "升序");
    T(DESCEND, "降序");

} // namespace NBillMenu
T(PRESS_ANY_KEY, "按任意键继续...");
namespace NWalletMenu
{
    T(TITLE, "////////// 我的钱包 //////////");
    T(BALANCE, "余额");
    T(NEGATIVE_BALANCE_WARNING, "余额小于零, 请合理消费");
    T(TOP_UP, "充值");
    T(WITHDRAW, "转出");
    T(EDIT, "编辑");
    T(BACK, "返回");
    T(END, "////////// ＝＝＝＝ //////////");
} // namespace NWalletMenu

namespace NWallet
{
    T(TOP_UP, "充值");
    T(WITHDRAW, "转出");
    T(EDIT, "编辑");
} // namespace NWallet
#endif
