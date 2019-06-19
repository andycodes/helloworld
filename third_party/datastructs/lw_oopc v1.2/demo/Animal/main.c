#include "animal.h"

int main()
{
    Fish* fish = Fish_new();    // ���������
    Dog* dog = Dog_new();       // ����������
    Car* car = Car_new();       // �������Ӷ���

    Animal* animals[2] = { 0 };     // ��ʼ������������������Animalָ������)
    IMoveable* moveObjs[3] = { 0 }; // ��ʼ�����ƶ�����������������IMoveableָ������)

    int i = 0;                  // i��j��ѭ������
    int j = 0;

    // ��ʼ���������ǳ�Ϊ��С���㣬����Ϊ��1��
    fish->init(fish, "Small carp", 1);

    // ��fishָ��ת��ΪAnimal����ָ�룬����ֵ��animals����ĵ�һ����Ա
    animals[0] = SUPER_PTR(fish, Animal);

    // ��ʼ����������ǳ�Ϊ������Ȯ������Ϊ��2��
    dog->init(dog, "sheepdog", 2);

    // ��dogָ��ת��ΪAnimal����ָ�룬����ֵ��animals����ĵڶ�����Ա
    animals[1] = SUPER_PTR(dog, Animal);

    // ��fishָ��ת��ΪIMoveable�ӿ�����ָ�룬����ֵ��moveOjbs����ĵ�һ����Ա
    moveObjs[0] = SUPER_PTR(fish, IMoveable);

    // ��dogָ��ת��ΪIMoveable�ӿ�����ָ�룬����ֵ��moveOjbs����ĵڶ�����Ա
    moveObjs[1] = SUPER_PTR(dog, IMoveable);

    // ��carָ��ת��ΪIMoveable�ӿ�����ָ�룬����ֵ��moveOjbs����ĵ�������Ա
    moveObjs[2] = SUPER_PTR(car, IMoveable);

    // ѭ����ӡ���������ڵĶ�����Ϣ
    for(i=0; i<2; i++)
    {
        Animal* animal = animals[i];
        animal->eat(animal);
        animal->breathe(animal);
        animal->sayHello(animal);
    }

    // ѭ����ӡ���ƶ����������ڵĿ��ƶ������ƶ���ʽ����Ϣ
    for(j=0; j<3; j++)
    {
        IMoveable* moveObj = moveObjs[j];
        moveObj->move(moveObj);
    }

    lw_oopc_delete(fish);
    lw_oopc_delete(dog);
    lw_oopc_delete(car);

    return 0;
}
