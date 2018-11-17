#version 450 core
			//冯氏着色(Phong Shading)
			in vec3 fNormal;
			in vec3 fPosition;
			in vec2 fCoord;
			out vec4 Color;
			#define NR_POINT_LIGHTS 4
			//物体材质
			struct Materials{
				sampler2D diffuse;
				sampler2D specular;
				float shininess;
			};

			//定向光
			struct DirLight{
				vec3 direction;
				vec3 ambient;
				vec3 diffuse;
				vec3 specular;
			};
			//点光源
			struct PointLight{
			vec3 position;
			float constant;
			float linear;
			float quadratic;
			vec3 ambient;
			vec3 diffuse;
			vec3 specular;
			};
			//投光物
			struct SpotLight{
			vec3 position;
			vec3 direction;
			float cutOff;
			float outerCutOff;
			float constant;
			float linear;
			float quadratic;
			vec3 ambient;
			vec3 diffuse;
			vec3 specular;
			};

			uniform DirLight dir_light;
			uniform PointLight point_lights[NR_POINT_LIGHTS];
			uniform SpotLight spot_light;

			uniform Materials material;
			uniform vec3 ucamera_position;

			vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
			vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
			vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

			void main() {

			vec3 viewDir = normalize(ucamera_position - fPosition);
			vec3 normal = normalize(fNormal);

			vec3 result = CalcDirLight(dir_light, normal, viewDir);

			 for(int i = 0; i < NR_POINT_LIGHTS; i++){
			result += CalcPointLight(point_lights[i], normal, fPosition, viewDir);
			}
			Color = vec4(result, 1.0f);
			};
			vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir){
			vec3 lightDir = normalize(-light.direction);
			float diff = max(dot(normal, lightDir), 0.0);
			vec3 reflectDir = reflect(-lightDir, normal);
			float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
			vec3 ambient = light.ambient * vec3(texture(material.diffuse, fCoord));
			vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, fCoord));
			vec3 specular = light.specular * spec * vec3(texture(material.specular, fCoord));
			return (ambient + diffuse + specular);
			}

			vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
			vec3 lightDir = normalize(light.position - fragPos);
			float diff = max(dot(normal, lightDir), 0.0);
			vec3 reflectDir = reflect(-lightDir, normal);
			float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
			float distance = length(light.position - fragPos);
			float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
			vec3 ambient = light.ambient * vec3(texture(material.diffuse, fCoord));
			vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, fCoord));
			vec3 specular = light.specular * spec * vec3(texture(material.specular, fCoord));
			ambient *= attenuation;
			diffuse *= attenuation;
			specular *= attenuation;
			return (ambient + diffuse + specular);
			};
