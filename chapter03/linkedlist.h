/*
    链表
    所有操作分为两类:(依据可否修改)
    - 1.静态(仅读入):get,search
    - 2.动态(需写入):insert remove

    链表
    其中基本元素是结点(node),所有结点通过指针连接起来,在逻辑上形成线性序列
    前后相邻的结点称为前驱和后继,若前驱或者后继存在,则必唯一.
    没有前驱的结点:首结点           没有后继的结点:末结点

    链表
    数组是随机访问,链表是顺序访问.但是也可以重载运算符[]来按索引求值

    链表(ADT)
    如果按索引来分:
    头结点:-1
    首结点:0
    末结点:n-1
    尾结点:n
    常用接口
*/
#include "node.h" // 包含结点头文件

template <typename T>
class LinkedList
{
private:
    int _size;       // 规模
    Posi(T) header;  // 头结点(头哨兵)
    Posi(T) trailer; // 尾结点(尾哨兵)
protected:
    void init();                     // 初始化链表
    void copyNode(Posi(T) p, int n); // 主要用于构造函数

public:
    LinkedList()
    {
        init(); // 原来忘记初始化了

    }; // 默认构造
    LinkedList(LinkedList<T> const &l);            // 复制构造
    ~LinkedList();                                 // 析构函数
    Posi(T) insertAsBefore(Posi(T) p, T const &e); // 在一结点处插入前驱结点
    Posi(T) insertAsAfter(Posi(T) p, T const &e);  // 在一节点处插入后继结点
    Posi(T) insertAsFirst(T const &e);             // 首插,插入作为第一个结点
    Posi(T) insertAsLast(T const &e);              // 尾插,插入作为最后一个结点
    Posi(T) first();                               // 返回首节点
    Posi(T) last();                                // 返回末节点
    int size();                                    // 获取结点数目
    T remove(Posi(T) p);                           // 删除合法位置p处的结点，并返回其数据值
    void clear();                                  // 清空列表中可见结点(不包括头尾结点)
    Posi(T) find(T const &e, int n, Posi(T) p);    // 在p结点向前查找n个元素，使其值为e,返回最右边的一个结点
    Posi(T) find(T const &e, Posi(T) p, int n);    // P结点向后查找n个元素，其实查找符合条件的第一个值
    int deduplicate();                             // 无序列表去重
    int uniquify();                                // 有序列表去重
    Posi(T) search(T const &e, int n, Posi(T) p);  // 有序列表的查找
    Posi(T) selectMax(Posi(T) p, int n);           // 从起始位置p开始的n个元素中选出最大者
    void selectionSorted(Posi(T) p, int n);        // 对列表中起始位置为p的连续n个元素做选择排序
    void insertSorted(Posi(T) p, int n);           // 对列表中起始位置为p的连续n个元素做插入排序
};

template <typename T>
void LinkedList<T>::init()
{
    // 初始化
    // 用来辅助构造函数的
    header = new ListNode<T>;                        // 创建头结点
    trailer = new ListNode<T>;                       // 创建尾结点
    header->pred = nullptr, header->succ = trailer;  // 头尾结点互联
    trailer->pred = header, trailer->succ = nullptr; // 头尾结点互联
    _size = 0;                                       // 记录链表规模
}
template <typename T>
Posi(T) LinkedList<T>::insertAsBefore(Posi(T) p, T const &e)
{
    // 在P结点前插入一个结点,结点元素为e
    // 1.创建新结点
    Posi(T) newP = new ListNode<T>;
    newP->data = e;
    newP->pred = p->pred;
    newP->succ = p;
    // 2.互联
    p->pred->succ = newP;
    p->pred = newP;
    _size++;
    return newP;
}
template <typename T>
Posi(T) LinkedList<T>::insertAsAfter(Posi(T) p, T const &e)
{
    // 在P结点后插入一个结点,结点元素为e
    // 1.创建新结点
    Posi(T) newP = new ListNode<T>; // 此时保存元素为e,前驱结点为p,后继为p结点的后继
    newP->data = e;
    newP->pred = p;
    newP->succ = p->succ;
    // 2.结点间互联
    p->succ->pred = newP;
    p->succ = newP;
    _size++;
    return newP;
}
template <typename T>
Posi(T) LinkedList<T>::insertAsFirst(T const &e)
{
    return insertAsAfter(header, e); // 实际相当于insertAsAfter(header,e)
}
template <typename T>
Posi(T) LinkedList<T>::insertAsLast(T const &e)
{
    return insertAsBefore(trailer, e); // 实际相当于insertAsBefore(trailer,e)
}
template <typename T>
void LinkedList<T>::copyNode(Posi(T) p, int n)
{
    // 通过复制别的链表来创建新的链表
    init(); // 初始化
    while (n--)
    { // 挨个复制
        insertAsLast(p->data);
        p = p->succ;
    }
}
template <typename T>
LinkedList<T>::LinkedList(LinkedList<T> const &l)
{ // 复制构造
    copyNode(l.frist(), l.size());
}
template <typename T>
Posi(T) LinkedList<T>::first()
{
    return header->succ;
}
template <typename T>
Posi(T) LinkedList<T>::last()
{
    return trailer->pred;
}
template <typename T>
int LinkedList<T>::size()
{
    return _size;
}
template <typename T>
T LinkedList<T>::remove(Posi(T) p)
{
    // 1.取出数据值
    T temp = p->data;
    // 2.更改链接关系
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    // 3.删除结点
    delete p;
    // 4.更改结点规模
    _size--;
    // 5.返回结点数据
    return temp;
}
template <typename T>
void LinkedList<T>::clear()
{
    // 不断的删除头结点的后继，直至清空。
    while (0 < _size)
    {
        remove(header->succ);
    }
}
template <typename T>
LinkedList<T>::~LinkedList()
{
    // 1.首先删除链表中可见结点
    clear();
    // 2.删除头尾结点
    delete header;
    delete trailer;
}
template <typename T>
Posi(T) LinkedList<T>::find(T const &e, int n, Posi(T) p)
{
    // 向前查找n个结点
    while (0 < n--)
    {
        if (e == p->pred->data)
        {
            return p->pred;
        }
        p = p->pred;
    }
    return nullptr; // 如果没有找到
}
template <typename T>
Posi(T) LinkedList<T>::find(T const &e, Posi(T) p, int n)
{
    // 向后查找n个结点
    while (0 < n--)
    {
        if (e == p->succ->data)
        {
            return p->succ;
        }
        p = p->succ;
    }
    return nullptr;
}
template <typename T>
int LinkedList<T>::deduplicate()
{
    // 1.如果元素少于2个则直接返回0
    if (_size < 2)
        return 0;
    // 2.保存老元素个数
    int oldSize = _size;
    // 3.从第二个元素开始，挨个比较其前驱
    Posi(T) p = header->succ->succ;
    int r = 1;
    while (p != trailer)
    {
        Posi(T) temp = find(p->data, r, p);
        if (temp != nullptr)
        {
            remove(temp);
        }
        else
        {
            r++;
        }
        p = p->succ;
    }
    return oldSize - _size;
}
template <typename T>
int LinkedList<T>::uniquify()
{
    // 有序列表的去重 O(n)
    // 1.如果个数少于2,直接返回
    if (_size < 2)
        return 0;
    // 2.保存现有元素个数
    int oldSize = _size;
    // 3.创建双指针依次迭代
    Posi(T) p = first();
    Posi(T) q;
    while (trailer != (q = p->succ))
    {
        if (p->data != q->data)
        {
            p = q;
        }
        else
        {
            remove(q);
        }
    }
    return oldSize - _size;
}
template <typename T>
Posi(T) LinkedList<T>::search(T const &e, int n, Posi(T) p)
{
    // 在p结点的前n个真前驱中,查找到第一个不大于e的结点(<=e)
    // 1.其实就是顺序查找
    if (p->data == e)
        return p;
    do
    {
        p = p->pred, n--;
        if (p->data == e)
            return p;
    } while ((-1 != n) && p != header);
    return p;
}
template <typename T>
Posi(T) LinkedList<T>::selectMax(Posi(T) p, int n)
{
    //  在起始位置为P的n个元素中,查找最大值
    // 双指针算法
    Posi(T) q = p;
    Posi(T) max = p;
    do
    {
        q = q->succ, n--;
        if (q->data >= max->data)
            max = q;
    } while (1 < n); // 为什么是n>1呢
    return max;
}
template <typename T>
void LinkedList<T>::selectionSorted(Posi(T) p, int n)
{
    // 对列表中起始位置为p的连续n个元素做选择排序
    // 1.给定查找区间[p,p+n)(head,tail)
    Posi(T) head = p->pred;
    Posi(T) tail = p;
    for (int i = 0; i < n; i++)
        tail = tail->succ;
    // 2.开始排序
    while (n-- > 1)
    {
        // 反复从待排序区间内找出最大值,移动到有序序列的前端
        insertAsBefore(tail, remove(selectMax(head->succ, n)));
        tail = tail->pred;
    }
}
template <typename T>
void LinkedList<T>::insertSorted(Posi(T) p, int n)
{
    // 有结点p开始的n的元素进行插入排序
    // 双指针
    // 时间复杂度:最好情况有序,每次插入都是一次比较,零次插入 O(n);
    //           最坏情况逆序,每次插入都是
    for (int i = 0; i < n; i++)
    {
        insertAsAfter(search(p->data, i, p), p->data);
        p = p->succ;
        remove(p->pred);
    }
}