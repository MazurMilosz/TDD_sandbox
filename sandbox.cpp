#include <gmock/gmock.h>

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


class DummyStack
{
public:
    unsigned int size() const
    {
        return m_storage.size();
    }

    void push(int p_element)
    {
       m_storage.push_back(p_element);
    }

    int pop()
    {
        auto ret = m_storage.back();
        m_storage.pop_back();
        return ret;
    }
private:
    std::vector<int> m_storage;
};


TEST(StackTest, emptyStackShouldReturnZeroSize)
{
    auto stack = DummyStack{};
    ASSERT_EQ(0u, stack.size());
}

TEST(StackTest, shouldIncreaseSizeWithPushes)
{
    auto stack = DummyStack{};
    stack.push(2);
    stack.push(5);
    ASSERT_EQ(2u, stack.size());
}

TEST(StackTest, shouldDecreaseSizeWithPop)
{
    auto stack = DummyStack{};
    stack.push(2);
    stack.pop();
    ASSERT_EQ(0u, stack.size());
}

TEST(StackTest, shouldPopElementsInLastInFirstOutOrder)
{
    auto stack = DummyStack{};
    stack.push(1);
    stack.push(2);
    ASSERT_EQ(2, stack.pop());
    ASSERT_EQ(1, stack.pop());
}
