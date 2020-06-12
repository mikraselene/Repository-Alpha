#ifndef TEXT_H
#define TEXT_H

#include <iostream>

#define CLEAR system("printf \"\033c\"")
//#define CLEAR system("clear")
//#define CLEAR system("cls")

#define T(code, text) const std::string(code) = (text)

namespace NMenu
{
    T(TITLE, "/////////// 主菜单 ///////////");
    T(ASSET_MENU, "财产");
    T(BILL_MENU, "账单");
    T(WALLET_MENU, "钱包");
    T(FILE_MENU, "文件");
    T(REFRESH_MENU, "刷新");
    T(EXIT, "退出");
    T(ASSET_TITLE, "////////// 财产菜单 //////////");
    T(TRANSACTION_MENU, "收入和支出");
    T(DEPO_AND_LOAN_MENU, "存款和贷款");
    T(BACK, "返回");
    T(END, "////////// ＝＝＝＝ //////////");
    T(TRANSACTION_TITLE, "////////// 收支菜单 //////////");
    T(ADD_SINGLE_EXPENSE, "添加单笔支出");
    T(ADD_SINGLE_INCOME, "添加单笔收入");
    T(ADD_REGULAR_EXPENSE, "添加定期支出");
    T(ADD_REGULAR_INCOME, "添加定期收入");
    T(EDIT_TRANSACTION, "编辑收支");
    T(DELETE_TRANSACTION, "删除收支");
    T(DEPO_AND_LOAN_TITLE, "////////// 存贷菜单 //////////");
    T(ADD_DEPOSIT, "添加存款");
    T(ADD_LOAN, "添加贷款");
    T(EDIT, "编辑存贷");
    T(STATISTICS, "统计");
    T(BILL_TITLE, "////////// 账单菜单 //////////");
    T(OVERVIEW, "总览");
    T(FILTER, "过滤器");
    T(OVERVIEW_TITLE, "//////////// 总览 ////////////");
    T(OVERVIEW_END, "//////////// ＝＝ ////////////");
    T(BY_DATE, "按日期");
    T(BY_AMOUNT, "按金额");
    T(ASCEND, "升序");
    T(DESCEND, "降序");
    T(FILTER_TITLE, "/////////// 过滤器 ///////////");
    T(FILTER_BY_DATE, "按日期过滤");
    T(FILTER_BY_AMOUNT, "按金额过滤");
    T(FILTER_BY_TYPE, "按类别过滤");
    T(LOWER_LIMIT, "下限");
    T(UPPER_LIMIT, "上限");
} // namespace NMenu

namespace NTransaction
{
    T(SINGLE_EXPENSE_TITLE, " 单笔支出 ");
    T(SINGLE_INCOME_TITLE, " 单笔收入 ");
    T(REGULAR_EXPENSE_TITLE, " 定期支出 ");
    T(REGULAR_INCOME_TITLE, " 定期收入 ");
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
    T(INCOME, "收入");
    T(EXPENSE, "支出");
    T(TYPE, "种类");
    T(EDIT, "编辑");
    T(DELETE, "删除");
    T(BACK, "返回");
    T(ID, "编号");
} // namespace NTransaction

namespace NDepositAndLoan
{
    T(TITLE, " 存贷交易 ");
    T(YUAN, "元");
    T(TOTAL_INCOME, "来自利息的总收入");
    T(TOTAL_EXPENSE, "来自利息的总支出");
    T(CHOOSE_A_DEPOSIT_OR_LOAN, "根据编号选择一个存贷");
    T(PRESS_ENTER_TO_EXIT, "按下回车或输入 0 返回");
    T(DEPOSIT, "存款");
    T(LOAN, "贷款");
    T(TYPE, "种类");
    T(ID, "编号");
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
    T(RATE_HELP, "利率前标记'S'的是单利, 标记'C'的是复利. ");
    T(DELETE, "删除");
    T(EDIT, "编辑");
    T(BACK, "返回");
} // namespace NDepositAndLoan

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

namespace NWallet
{
    T(TITLE, "////////// 我的钱包 //////////");
    T(BALANCE, "余额");
    T(NEGATIVE_BALANCE_WARNING, "\033[31m余额小于零, 请合理消费\033[0m");
    T(TOP_UP, "充值");
    T(WITHDRAW, "转出");
    T(EDIT, "编辑");
    T(BACK, "返回");
    T(END, "////////// ＝＝＝＝ //////////");
} // namespace NWallet

namespace NFile
{
    T(TITLE, "////////// 文件菜单 //////////");
    T(SAVE, "保存");
    T(SAVED, "\033[32m文件已保存\033[0m");
    T(LOADED, "\033[32m文件已读取\033[0m");
    T(NOT_LOADED, "文件未读取");
    T(ARE_YOU_SURE, "确定读取吗? (\033[32my\033[0m/n)");
    T(LOAD, "读取");
    T(BACK, "返回");
    T(END, "////////// ＝＝＝＝ //////////");
} // namespace NFile

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
} // namespace NPeriod

namespace NDate
{
    T(YEAR, "年");
    T(MONTH, "月");
    T(DAY, "日");
} // namespace NDate

namespace NInstruction
{
    T(COMFIRM_AND_SAVE, "确认并保存");
    T(INPUT_AGAIN, "重新输入");
    T(BACK, "返回");
} // namespace NInstruction

namespace NError
{
    T(CANNOT_OPEN_FILE, "找不到文件, 已创建新的空文件");
    T(ILLEGAL_OPERATION, "\033[31m不合法的运算\033[0m");
    T(ILLEGAL_CATEGORY, "\033[31m不合法的类别\033[0m");
    T(ILLEGAL_NUMBER, "\033[31m不合法的数字\033[0m");
    T(NEGATIVE_NUMBER, "\033[31m输入不能为负数\033[0m");
    T(ILLEGAL_DATE, "\033[31m不合法的日期\033[0m");
    T(PLEASE_INPUT_AGAIN, "请重新输入");
} // namespace NError

namespace NSystem
{
    T(DELETED, "\033[32m删除成功\033[0m");
    T(PRESS_ANY_KEY, "按任意键继续...");
} // namespace NSystem

#endif
