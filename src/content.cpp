#include "content.h"

const QVector<ElementInfo> &elementCatalog()
{
    static const QVector<ElementInfo> data = {
        {QStringLiteral("木"), QStringLiteral("生发、条达"),
         QStringLiteral("肝"), QStringLiteral("胆"), QStringLiteral("目"), QStringLiteral("筋"),
         QStringLiteral("春"), QStringLiteral("怒"), QStringLiteral("酸"), QStringLiteral("青"),
         QColor(46, 160, 90), QStringLiteral("震、巽"),
         QStringLiteral("生火"), QStringLiteral("克土"),
         QStringLiteral("宜疏肝理气、早睡早起、多望远。大怒伤肝，情志宜舒不宜郁。")},
        {QStringLiteral("火"), QStringLiteral("温热、向上"),
         QStringLiteral("心"), QStringLiteral("小肠"), QStringLiteral("舌"), QStringLiteral("脉"),
         QStringLiteral("夏"), QStringLiteral("喜"), QStringLiteral("苦"), QStringLiteral("赤"),
         QColor(220, 70, 70), QStringLiteral("离"),
         QStringLiteral("生土"), QStringLiteral("克金"),
         QStringLiteral("宜养心安神、午时稍歇、饮食清淡。过喜或焦躁都扰动心神。")},
        {QStringLiteral("土"), QStringLiteral("生化、承载"),
         QStringLiteral("脾"), QStringLiteral("胃"), QStringLiteral("口"), QStringLiteral("肉"),
         QStringLiteral("长夏"), QStringLiteral("思"), QStringLiteral("甘"), QStringLiteral("黄"),
         QColor(210, 160, 50), QStringLiteral("坤、艮"),
         QStringLiteral("生金"), QStringLiteral("克水"),
         QStringLiteral("宜规律饮食、忌暴饮暴食与过思。脾喜燥恶湿，可适度运动助运化。")},
        {QStringLiteral("金"), QStringLiteral("收敛、肃降"),
         QStringLiteral("肺"), QStringLiteral("大肠"), QStringLiteral("鼻"), QStringLiteral("皮"),
         QStringLiteral("秋"), QStringLiteral("悲"), QStringLiteral("辛"), QStringLiteral("白"),
         QColor(180, 190, 210), QStringLiteral("兑、乾"),
         QStringLiteral("生水"), QStringLiteral("克木"),
         QStringLiteral("宜润肺防燥、早卧早起、保持呼吸通畅。过度悲伤最耗肺气。")},
        {QStringLiteral("水"), QStringLiteral("寒润、闭藏"),
         QStringLiteral("肾"), QStringLiteral("膀胱"), QStringLiteral("耳"), QStringLiteral("骨"),
         QStringLiteral("冬"), QStringLiteral("恐"), QStringLiteral("咸"), QStringLiteral("黑"),
         QColor(70, 130, 200), QStringLiteral("坎"),
         QStringLiteral("生木"), QStringLiteral("克火"),
         QStringLiteral("宜早卧晚起、避寒保暖、节欲养精。惊吓与过劳最伤肾精。")},
    };
    return data;
}

const QVector<TrigramInfo> &trigramCatalog()
{
    static const QVector<TrigramInfo> data = {
        {QStringLiteral("乾"), QStringLiteral("☰"), QStringLiteral("天、健"), QStringLiteral("头"),
         QStringLiteral("肺、大肠（金）"), QStringLiteral("《说卦》以乾为首。乾主刚健，对应清肃、统领，常与呼吸系统的宣降功能对照来理解。")},
        {QStringLiteral("坤"), QStringLiteral("☷"), QStringLiteral("地、顺"), QStringLiteral("腹"),
         QStringLiteral("脾、胃（土）"), QStringLiteral("坤为腹、为母、为养。脾胃居中焦，像大地运化水谷，化生气血。")},
        {QStringLiteral("震"), QStringLiteral("☳"), QStringLiteral("雷、动"), QStringLiteral("足"),
         QStringLiteral("肝、胆（木）"), QStringLiteral("震为足、为动。肝主疏泄、主筋，春生之气如雷发动，宜活动筋骨。")},
        {QStringLiteral("巽"), QStringLiteral("☴"), QStringLiteral("风、入"), QStringLiteral("股、四肢"),
         QStringLiteral("肝（木）"), QStringLiteral("巽为风、为入。风气通肝，过敏、游走不适等现象，传统上常从风木来讨论。")},
        {QStringLiteral("坎"), QStringLiteral("☵"), QStringLiteral("水、陷"), QStringLiteral("耳"),
         QStringLiteral("肾、膀胱（水）"), QStringLiteral("坎为耳、为水。肾开窍于耳、主骨生髓，冬藏之象与坎水相应。")},
        {QStringLiteral("离"), QStringLiteral("☲"), QStringLiteral("火、明"), QStringLiteral("目"),
         QStringLiteral("心、小肠（火）"), QStringLiteral("离为目、为火。心主血脉、藏神；目得血而能视，神明清则目光有神。")},
        {QStringLiteral("艮"), QStringLiteral("☶"), QStringLiteral("山、止"), QStringLiteral("手"),
         QStringLiteral("脾胃、肌（土）"), QStringLiteral("艮为手、为止。山止而不迁，提示劳作有度、过劳则伤形。")},
        {QStringLiteral("兑"), QStringLiteral("☱"), QStringLiteral("泽、悦"), QStringLiteral("口"),
         QStringLiteral("肺、大肠（金）"), QStringLiteral("兑为口、为悦。口鼻是气与饮食的门户，言语过多、秋燥都与金气相关。")},
    };
    return data;
}

const QVector<SeasonInfo> &seasonCatalog()
{
    static const QVector<SeasonInfo> data = {
        {QStringLiteral("春"), QStringLiteral("木"),
         QStringLiteral("雷水解冻，万物发生。卦气上多应震、巽，强调「动」与「疏」。"),
         QStringLiteral("养肝。夜卧早起，缓步于庭；少食酸增、避免暴怒。")},
        {QStringLiteral("夏"), QStringLiteral("火"),
         QStringLiteral("离火当令，光明盛大。宜「明」心神，而不是一味亢奋。"),
         QStringLiteral("养心。晚睡早起，适当午睡；清淡饮食，忌熬夜耗神。")},
        {QStringLiteral("长夏"), QStringLiteral("土"),
         QStringLiteral("坤土居中，承上启下。易学里「中」不是空，而是运化的枢纽。"),
         QStringLiteral("养脾。湿气偏盛，饮食宜温燥有度，少冷饮、少久坐。")},
        {QStringLiteral("秋"), QStringLiteral("金"),
         QStringLiteral("兑、乾主收敛。天高气清，对应「肃降」而不是继续生发。"),
         QStringLiteral("养肺。早卧早起，防燥；少悲忧，保持呼吸与情绪舒畅。")},
        {QStringLiteral("冬"), QStringLiteral("水"),
         QStringLiteral("坎水闭藏。潜龙勿用，不是颓废，而是蓄积明年的生发。"),
         QStringLiteral("养肾。早卧晚起，避寒；节制夜生活，保护睡眠与腰膝。")},
    };
    return data;
}

QString homeIntroHtml()
{
    return QStringLiteral(R"(
<h2>易医之间：用象来理解人</h2>
<p>《周易》讲的是阴阳消长、时位变化；中医讲的是藏象、气血、寒热虚实。两者都把人放进天地节律里看，这就是常说的「天人合一」。</p>
<p><b>不是把卦拿来看病，也不是把药方写进卦辞。</b>更稳妥的读法是：周易提供一套「象」的语言，中医用这套语言描述身体与季节的关系。</p>
<ul>
<li><b>阴阳</b>：表里、寒热、动静、气血。易学里的两仪，落到身体就是对立又互根的状态。</li>
<li><b>五行</b>：生克制化。木火土金水既描述季节气候，也描述肝心肺脾肾的功能倾向。</li>
<li><b>八卦</b>：《说卦传》把乾为首、坤为腹、坎为耳、离为目等，是身体部位的取象，不是解剖定位仪。</li>
<li><b>时</b>：春生、夏长、秋收、冬藏。养生首先是顺着时间做事，而不是堆补药。</li>
</ul>
<p>右侧几个栏目可以点开：先从五行对照表建立地图，再看八卦取象和四季作息。所有内容都是文化与医学史科普。</p>
)");
}

QString disclaimerHtml()
{
    return QStringLiteral(R"(
<h2>使用说明</h2>
<p>本软件是<strong>文化与中医科普</strong>工具，用来理解《周易》取象与中医藏象之间的历史联系。</p>
<ul>
<li>不能替代执业医师的问诊、检查与治疗。</li>
<li>不提供处方、不判断具体疾病、不做体质「确诊」。</li>
<li>不是占卜、算命或预测吉凶的工具。</li>
<li>身体不适请及时就医。自行停药、偏方或按卦养生造成的风险需自行避免。</li>
</ul>
<p>古代文献里的身体部位、情志、季节对应，属于当时的观察框架，与现代解剖学、传染病学不是同一套系统，阅读时请分开层次。</p>
)");
}
