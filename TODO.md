1. CodeTree 的构造函数右值引用问题，什么是左值，什么是右值
2. dynamic_cast 和 static_cast 区别
3. 函数形参后的const
    成员函数形参后的const：
    this指针本来就是const指针（常量指针），指向不能被再次修改，但是this指向对象没做const要求，此时this指针不能指向const对象，
    因为this指向对象要求是非const(可更改的)，但const对象不能更改。但如果按照作者文中给形参后加const表示this指向对象也要求是const对象，
    这时this指针可以指向非const对象，此时把非const对象看做是const对象。指向const对象的指针本来就是把指向对象当成const常量的一种指针，
    是他的一种“自以为是”
    如果是指向非const对象的指针指向了const对象，那么操作这个指针不断修改指向这个const对象的值不是与const对象const的要求冲突了吗

    const int v = 10;
    int *p1 = &v;   // 不合法
    const *p2 = &v;  // 合法

    使用效果：
    1. 如果成员函数形参后不加const，则不能使用const对象调用该方法，加上const后，既可以使用const对象调用该方法，也可以使用非const对象调用
    2. 同时告诉编译器：该方法不应该改变成员变量
    除了一种情况不适用于上述规则：使用了mutable关键字，形参后有const的函数可以修改成员变量

    Ref:
    https://www.cnblogs.com/yongdaimi/p/9565996.html
    https://stackoverflow.com/questions/2157458/using-const-in-classs-functions
    https://blog.csdn.net/whahu1989/article/details/80501685#comments_13976556