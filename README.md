# ԭ��
![���](framework.png)

�ڴ��������chunk���ɣ���ͬ��chunk�¹�����Ե�block����4�ֽڵ�chunk�µ�block�ռ�Ϊ4�ֽڣ�8�ֽڵ�chunk�µ�block�ռ�Ϊ8�ֽڣ��Դ����ƣ�һֱ��1024�ֽڵ�chunk��

������һ��N�ֽڵĿռ�ʱ���ڴ���ҵ�����>=N��chunk��Ȼ���������µ�block������һ�����е�block�����ַ��block��Ϊͷ��ʵ�壬ͷָ�����ڵ�chunk��ʵ����һ��union��δ������ʱָ����һ��block�����ѷ�������Ϊ��ʹ�û��棬��ʱblock����������������block����block��ʹ�����ͷź����¼��뵽��������

�������Ŀռ��1024���ڴ�ػ��´���һ����chunk���������·���һ��block���ڴ�ر����ٺ����з����ڴ涼�����ա�

# ʹ��
``` C++
MemoryPool* pool = new MemoryPool;
pool->report();
for (int i = 0; i < 1500; i++)
{
	char* str = (char*)pool->malloc(100);
	str[0] = 'm';
	pool->free(str);
}
pool->malloc(3000);
pool->report();
delete pool;
```
