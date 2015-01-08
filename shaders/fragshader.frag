 
uniform vec2 ex_Normal; //normals as computed in vertex shader
uniform float zoom;
uniform int iteration;

void main(void)
{
    vec2 temp, c;
    
    c.x = 1.3333 * (gl_TexCoord[0].x - .5) * scale - center.x;
    c.y = (gl_TexCoord[0].y - .5) * scale - center.y;
    
    for(int i = 0; x*x + y*y < 2*2 && i<iteration; i++){
        float x = ((temp.x * temp.x) - temp.y * temp.y) + c.x);
        float y = 2*(temp.x*temp.y)+c.y;
        temp.x = x;
        temp.x = y;
        }
    gl_FragColor = texture1D(tex, (1 == iteration ? 0.0 : float(i)) / 100.0);
}
